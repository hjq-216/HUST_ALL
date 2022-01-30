#include "common.h"
#include "cpu/decode.h"
#include "cpu/exec.h"
#include "debug.h"
#include "isa/rtl.h"
#include "nemu.h"
#include "rtl/rtl-wrapper.h"
#include "rtl/rtl.h"
#include <stdint.h>
#include <stdio.h>

// 根据打印结果得到

#define SSTATUS 0x100
#define STVEC   0x105
#define SEPC    0x141
#define SCAUSE  0x142
#define SATP    0x180

// csr的值解析在id_src2->val
rtlreg_t* CSRS(uint32_t csr) {
    switch (csr) {
        case SSTATUS:
            return &cpu.csr.sstatus;
        case STVEC:
            return &cpu.csr.stvec;
        case SEPC: 
            return &cpu.csr.sepc;
        case SCAUSE:
            return &cpu.csr.scause;
        case SATP:
            return &cpu.csr.satp;
        default:
            Assert(0, "csr:%x not implement", csr);
    }
}

make_EHelper(csrrs) {
    id_dest->val = *CSRS(id_src2->val);
    rtl_or(CSRS(id_src2->val), &id_src->val, &id_dest->val);
    rtl_sr(id_dest->reg, &id_dest->val, 4);
    print_asm_template3(csrrs);
}

make_EHelper(csrrw) {
    id_dest->val = *CSRS(id_src2->val);
    *CSRS(id_src2->val) = id_src->val;
    rtl_sr(id_dest->reg, &id_dest->val, 4);
    print_asm_template3(csrrw);
}

/*
* 80100a44 <_yield>:
* 80100a44:	fff00893          	li	a7,-1
* 80100a48:	00000073          	ecall
* 80100a4c:	00008067          	ret
* 把a7寄存器的值放入NO
*/
make_EHelper(ecall) {
    switch (decinfo.isa.instr.simm11_0) {
        // ecall
        case 0b000000000000:
            raise_intr(reg_l(17), cpu.pc);
            print_asm_template1(ecall); 
            break;
        // sret
        case 0b000100000010:
            // PA不涉及特权级的切换, RTFM的时候你不需要关心和特权级切换相关的内容.
            // 保存的是自陷指令的PC, 因此需要在适当的地方对保存的PC加上4, 使得将来返回到自陷指令的下一条指令.
            rtl_addi(&decinfo.jmp_pc, CSRS(SEPC), 4);
            rtl_j(decinfo.jmp_pc);
            print_asm_template3(sret); 
            break;
        default:
            Assert(0, "[system order] funct3 000 error: not implement, csr: %d, pc=0x%08x", decinfo.isa.instr.csr, cpu.pc);
    }
}


