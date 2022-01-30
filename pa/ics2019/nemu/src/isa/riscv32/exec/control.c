#include "common.h"
#include "cpu/decode.h"
#include "cpu/exec.h"
#include "debug.h"
#include "isa/decode.h"
#include "isa/rtl.h"
#include "nemu.h"
#include "rtl/relop.h"
#include "rtl/rtl.h"
#include <stdint.h>

make_EHelper(jal) {
    id_dest->val = cpu.pc + 4;
    rtl_sr(id_dest->reg, &id_dest->val, 4);
    rtl_add(&decinfo.jmp_pc, &id_src->val, &cpu.pc);
    rtl_j(decinfo.jmp_pc);
    print_asm_template2(jal);
}

make_EHelper(jalr) {
    id_dest->val = cpu.pc + 4;
    rtl_add(&decinfo.jmp_pc, &id_src->val, &id_src2->val);
    rtl_sr(id_dest->reg, &id_dest->val, 4);
    rtl_j(decinfo.jmp_pc);
    difftest_skip_dut(1, 2); //difftest
    print_asm_template2(jalr);
}

// branch 根据funct3进行解析得到relop
static uint32_t branch_table[8] = {
    RELOP_EQ, RELOP_NE, RELOP_FALSE, RELOP_FALSE, RELOP_LT, RELOP_GE, RELOP_LTU, RELOP_GEU
};

make_EHelper(branch) {
    rtl_add(&decinfo.jmp_pc, &id_dest->val, &cpu.pc);
    rtl_jrelop(branch_table[decinfo.isa.instr.funct3], &id_src->val, &id_src2->val, decinfo.jmp_pc);
    switch (branch_table[decinfo.isa.instr.funct3]) {
        case RELOP_EQ:
            print_asm_template3(beq);
            break;
        case RELOP_NE:
            print_asm_template3(bne);
            break;
        case RELOP_GE:
            print_asm_template3(bge);
            break;
        case RELOP_LT:
            print_asm_template3(blt);
            break;
        case RELOP_LTU:
            print_asm_template3(bltu);
            break;
        case RELOP_GEU:
            print_asm_template3(bgeu);
            break;
        default:
            Assert(0, "error funct3 in branch_table: %d, pc=0x%08x", decinfo.isa.instr.funct3, cpu.pc);
    }
}