#include "nemu.h"
#include "monitor/diff-test.h"
#include <stdbool.h>
#include <stdio.h>

const char *ref_regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void ref_reg_display(CPU_state *ref_r) {
  printf("QEMU REGS: \n");
  for(int i = 0; i < 32; ++i){
    printf("%s  %x\n", ref_regs[i], ref_r->gpr[i]._32);
  }
  printf("stevc: %x\n", ref_r->csr.stvec);
  printf("sstatus: %x\n", ref_r->csr.sstatus);
  printf("sepc: %x\n", ref_r->csr.sepc);
  printf("scause: %x\n", ref_r->csr.scause);
}

// after this function, programe will call isa_reg_display
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  for(int i = 0; i < 32; ++i) {
    if (ref_r->gpr[i]._32 != reg_l(i)) {
      ref_reg_display(ref_r);
      printf("error at pc=0x%08x\n", cpu.pc);
      printf("NEMU REGS: \n");
      return false;
    }
  }
  return true;
}

void isa_difftest_attach(void) {
}
