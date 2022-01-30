#include "common.h"
#include "cpu/decode.h"
#include "debug.h"
#include "memory/memory.h"
#include "nemu.h"
#include <stdint.h>

#define PTE_V 0x01
#define PTE_R 0x02
#define PTE_W 0x04
#define PTE_X 0x08
#define PTE_U 0x10
// Page directory and page table constants
#define NR_PDE    1024    // # directory entries per page directory
#define NR_PTE    1024    // # PTEs per page table
#define PGSHFT    12      // log2(PGSIZE)
#define PTXSHFT   12      // Offset of PTX in a linear address
#define PDXSHFT   22      // Offset of PDX in a linear address

// +--------10------+-------10-------+---------12----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDX(va) --/ \--- PTX(va) --/\------ OFF(va) ------/
//  \--- VPN[1] ---/ \--- VPN[0] ---/\------ OFF(va) ------/
typedef uint32_t PTE;
typedef uint32_t PDE;
#define PDX(va)     (((uint32_t)(va) >> PDXSHFT) & 0x3ff)
#define PTX(va)     (((uint32_t)(va) >> PTXSHFT) & 0x3ff)
#define OFF(va)     ((uint32_t)(va) & 0xfff)

// Address in page table or page directory entry
#define PTE_ADDR(pte)   (((uint32_t)(pte) & ~0x3ff) << 2)

// construct virtual address from indexes and offset
#define PGADDR(d, t, o) ((uint32_t)((d) << PDXSHFT | (t) << PTXSHFT | (o)))

/*
*
1. Let a be satp.ppn × PAGESIZE, and let i = LEVELS − 1. (For Sv32, PAGESIZE=212 and
LEVELS=2.)
2. Let pte be the value of the PTE at address a+va.vpn[i]×PTESIZE. (For Sv32, PTESIZE=4.)
If accessing pte violates a PMA or PMP check, raise an access exception corresponding to
the original access type.
3. If pte.v = 0, or if pte.r = 0 and pte.w = 1, stop and raise a page-fault exception corresponding
to the original access type.
4. Otherwise, the PTE is valid. If pte.r = 1 or pte.x = 1, go to step 5. Otherwise, this PTE is a
pointer to the next level of the page table. Let i = i − 1. If i < 0, stop and raise a page-fault
exception corresponding to the original access type. Otherwise, let a = pte.ppn × PAGESIZE
and go to step 2.
5. A leaf PTE has been found. Determine if the requested memory access is allowed by the
pte.r, pte.w, pte.x, and pte.u bits, given the current privilege mode and the value of the
SUM and MXR fields of the mstatus register. If not, stop and raise a page-fault exception
corresponding to the original access type.
6. If i > 0 and pte.ppn[i − 1 : 0] ̸= 0, this is a misaligned superpage; stop and raise a page-fault
exception corresponding to the original access type.
7. If pte.a = 0, or if the memory access is a store and pte.d = 0, either raise a page-fault
exception corresponding to the original access type, or:
• Set pte.a to 1 and, if the memory access is a store, also set pte.d to 1.
• If this access violates a PMA or PMP check, raise an access exception corresponding to
the original access type.
• This update and the loading of pte in step 2 must be atomic; in particular, no intervening
store to the PTE may be perceived to have occurred in-between.
8. The translation is successful. The translated physical address is given as follows:
• pa.pgoff = va.pgoff.
• If i > 0, then this is a superpage translation and pa.ppn[i − 1 : 0] = va.vpn[i − 1 : 0].
• pa.ppn[LEVELS − 1 : i] = pte.ppn[LEVELS − 1 : i].
*/

uint32_t page_translate(vaddr_t va, int len) {
  uintptr_t a = cpu.csr.PPN * 4096;
  // Log("a=%x", a);
  uintptr_t pte1 = paddr_read(a + PDX(va) * 4, 4);
  // Log("pte1=%x", pte1);
  // i = 1
  if (((pte1 & PTE_R) == 1) || (pte1 & PTE_X) == 1) {
    uintptr_t ppn0 = PTX(va);
    uintptr_t ppn1 = (pte1 >> 22) & 0x3ff;
    uintptr_t pgoff = OFF(va);
    Log("ppn0=%x, ppn1=%x, pgoff=%x", ppn0, ppn1, pgoff);
    return PGADDR((pte1 >> 22) & 0x3ff, PTX(va), OFF(va));
  }
  // i = 0
  uintptr_t pte1_ppn = PTE_ADDR(pte1);
  a = pte1_ppn;
  // Log("a=%x", a);
  uintptr_t pte2 = paddr_read(a + PTX(va) * 4, 4);
  Log("pte2=%x", pte2);
  if (((pte2 & PTE_R) == 1) || (pte2 & PTE_X) == 1) {
    pte2 = PTE_ADDR(pte2);
    uintptr_t pgoff = OFF(va);
    Log("pte2=%x, pgoff=%x", pte2, pgoff);
    return pte2 + pgoff;
  }
  pte2 = PTE_ADDR(pte2);
  uintptr_t pgoff = OFF(va);
  Log("pte2=%x, pgoff=%x", pte2, pgoff);
  return pte2 + pgoff;
  Assert(0, "invalid page");

  // Log("%x", va);
  // uint32_t pte1 = paddr_read((cpu.csr.PPN) * 4096 + PDX(va) * 4, 4);
  // Log("%x", pte1);
  // if ((pte1 & PTE_X) || (pte1 & PTE_R) || (pte1 & PTE_W)) {
  //   return pte1;
  // }
  // uint32_t pte2 = paddr_read(PTE_ADDR(pte1) + PTX(va) * 4, 4);
  // Log("%x", pte2);
  // if ((pte2 & PTE_X) != 0 || (pte2 & PTE_R) != 0 || (pte2 & PTE_W) !=0) {
  //   return pte2;
  // }
  // Log("%x", PTE_ADDR(pte2) + OFF(va));
  // return PTE_ADDR(pte2) + OFF(va);
}

uint32_t isa_vaddr_read(vaddr_t addr, int len) {
  if (!cpu.csr.MODE) {
    return paddr_read(addr, len);
  }
  paddr_t paddr = page_translate(addr, len);
  return paddr_read(paddr, len);
}

void isa_vaddr_write(vaddr_t addr, uint32_t data, int len) {
  if (!cpu.csr.MODE) {
    paddr_write(addr, data, len);
    return;
  }
  paddr_t paddr = page_translate(addr, len);
  paddr_write(paddr, data, len);
}