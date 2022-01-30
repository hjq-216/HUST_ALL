#ifndef __RISCV32_REG_H__
#define __RISCV32_REG_H__

#include "common.h"
#include <stdint.h>

#define PC_START (0x80000000u + IMAGE_START)

typedef struct {
  struct {
    rtlreg_t _32;
  } gpr[32];

  vaddr_t pc;

  // csr
  struct {
    // stvec寄存器来存放异常入口地址
    rtlreg_t stvec;
    // sepc寄存器 - 存放触发异常的PC
    rtlreg_t sepc;
    // scause寄存器 - 存放触发异常的原因
    rtlreg_t scause;
    // sstatus寄存器 - 存放处理器的状态
    union {
      struct {
        uint32_t SD           : 1;	
        uint32_t sstatus_30_20 :11;	
        uint32_t MXR          : 1;	
        uint32_t SUM          : 1;	
        uint32_t sstatus_17   : 1;	
        uint32_t XS           : 2;	
        uint32_t FS           : 2;	
        uint32_t sstatus_12_9 : 4;	
        uint32_t SPP          : 1;	
        uint32_t sstatus_7_6    : 2;	
        uint32_t SPIE          : 1;	
        uint32_t UPIE        : 1;	
        uint32_t sstatus_3_2  : 2;	
        uint32_t SIE          : 1;	
        uint32_t UIE    : 1;
      };
      rtlreg_t sstatus;
    };
    // satp存放分页地址以及分页使能位
    union {
      struct {
        uint32_t PPN :22;
        uint32_t ASID   :9;
        uint32_t MODE :1;
      };
      rtlreg_t satp;
    };
  } csr;

} CPU_state;

static inline int check_reg_index(int index) {
  assert(index >= 0 && index < 32);
  return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)

static inline const char* reg_name(int index, int width) {
  extern const char* regsl[];
  assert(index >= 0 && index < 32);
  return regsl[index];
}

#endif
