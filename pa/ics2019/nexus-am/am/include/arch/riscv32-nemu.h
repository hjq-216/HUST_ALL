#ifndef __ARCH_H__
#define __ARCH_H__

struct _Context {
  // 根据trap.S：regs，cause，status，epc
  // uintptr_t epc, cause, gpr[32], status;
  uintptr_t gpr[32], cause, status, epc;
  struct _AddressSpace *as;
};

/*
* define ARGS_ARRAY ("ecall", "a7", "a0", "a1", "a2", "a0")
*/

#define GPR1 gpr[17]
#define GPR2 gpr[10]
#define GPR3 gpr[11]
#define GPR4 gpr[12]
#define GPRx gpr[10]

#endif
