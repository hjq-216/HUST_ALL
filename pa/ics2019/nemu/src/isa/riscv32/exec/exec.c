#include "cpu/exec.h"
#include "all-instr.h"
#include "cpu/decode.h"
#include "debug.h"

// ld: lbu,lhu,lw，因此lb，lh需要单独实现呢
static OpcodeEntry load_table [8] = {
  EX(lb), EX(lh), EXW(ld, 4), EMPTY, EXW(ld, 1), EXW(ld, 2), EMPTY, EMPTY
};

static make_EHelper(load) {
  decinfo.width = load_table[decinfo.isa.instr.funct3].width;
  idex(pc, &load_table[decinfo.isa.instr.funct3]);
}

/*
* 000: sb存字节
* 001: sh存半字
* 010: sw存字
*/
static OpcodeEntry store_table [8] = {
  EXW(st, 1), EXW(st, 2), EXW(st, 4), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
};

static make_EHelper(store) {
  decinfo.width = store_table[decinfo.isa.instr.funct3].width;
  idex(pc, &store_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry computei_table[8] = {
  EX(addi), EX(slli), EX(slti), EX(sltiu), EX(xori), EX(srai_srli), EX(ori), EX(andi)
};

static make_EHelper(computei) {
  decinfo.width = computei_table[decinfo.isa.instr.funct3].width;
  idex(pc, &computei_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry compute_table[8] = {
  EX(add_sub_mul), EX(sll_mulh), EX(slt), EX(sltu), EX(xor), EX(srl_sra_divu), EX(or), EX(and_remu)
};

static make_EHelper(compute) {
  decinfo.width = compute_table[decinfo.isa.instr.funct3].width;
  idex(pc, &compute_table[decinfo.isa.instr.funct3]);
}

/*
* 中文手册有误
* The assembler pseudoinstruction to read a CSR, CSRR rd, csr, is encoded as CSRRS rd, csr, x0
* The assembler pseudoinstruction to write a CSR, CSRW csr, rs1, is encoded as CSRRW x0, csr, rs1
* CSRWI csr, uimm, is encoded as CSRRWI x0, csr, uimm
*/
static OpcodeEntry system_table[8] = {
  EX(ecall), EX(csrrw), EX(csrrs), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
};

static make_EHelper(system) {
  decinfo.width = system_table[decinfo.isa.instr.funct3].width;
  idex(pc, &system_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry opcode_table [32] = {
  /*
  * opcode0-1位都是1，因此通过2-6位来表示不同的指令，b00表示00xxx，比如auipc：00101，则是第一行第6个
  * opcode相同，根据func3解析，因此需要额外的表进行译码
  * ret 实际上是一个伪指令， 汇编器会用jalr x0,x1,0来替换它
  */
  /* b00 */ IDEX(ld, load), EMPTY, EMPTY, EMPTY, IDEX(I, computei), IDEX(U, auipc), EMPTY, EMPTY,
  /* b01 */ IDEX(st, store), EMPTY, EMPTY, EMPTY, IDEX(R, compute), IDEX(U, lui), EMPTY, EMPTY,
  /* b10 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
  /* b11 */ IDEX(B, branch), IDEX(I, jalr), EX(nemu_trap), IDEX(J, jal), IDEX(I, system), EMPTY, EMPTY, EMPTY,
};

void isa_exec(vaddr_t *pc) {
  decinfo.isa.instr.val = instr_fetch(pc, 4);
  Assert(decinfo.isa.instr.opcode1_0 == 0x3, "pc: 0x%08x, instr: %d", *pc, decinfo.isa.instr.val);
  idex(pc, &opcode_table[decinfo.isa.instr.opcode6_2]);
}
