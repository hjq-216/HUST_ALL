#include "debug.h"
#include "nemu.h"
#include "rtl/rtl.h"

/*
* 1. 将当前PC值保存到sepc寄存器
* 2. 在scause寄存器中设置异常号
* 3. 从stvec寄存器中取出异常入口地址
* 4. 跳转到异常入口地址
*/
void raise_intr(uint32_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * That is, use ``NO'' to index the IDT.
   */
  cpu.csr.sepc = epc;
  cpu.csr.scause = NO;
  rtl_j(cpu.csr.stvec);
}

bool isa_query_intr(void) {
  return false;
}
