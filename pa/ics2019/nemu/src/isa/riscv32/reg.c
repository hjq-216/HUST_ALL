#include "common.h"
#include "nemu.h"

const char *regsl[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  for (size_t i = 0; i < 32; i++)
  {
    printf("%s  %x\n", regsl[i], cpu.gpr[i]._32);
  }
  printf("stevc: %x\n", cpu.csr.stvec);
  printf("sstatus: %x\n", cpu.csr.sstatus);
  printf("sepc: %x\n", cpu.csr.sepc);
  printf("scause: %x\n", cpu.csr.scause);
}

uint32_t isa_reg_str2val(const char *s, bool *success) {
  for(int i = 0; i < 32; i++) {
    if (strcmp(regsl[i], s) == 0) {
      return cpu.gpr[i]._32;
    }
  }
  *success = false;
  return 0;
}
