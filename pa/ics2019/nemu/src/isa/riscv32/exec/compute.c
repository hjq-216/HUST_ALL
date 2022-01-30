#include "cpu/decode.h"
#include "cpu/exec.h"
#include "debug.h"
#include "isa/rtl.h"
#include "nemu.h"
#include "rtl/rtl.h"
#include "rtl/relop.h"
#include <stdint.h>

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(auipc) {
  rtl_add(&id_dest->val, &cpu.pc, &id_src->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template2(auipc);
}

make_EHelper(addi) {
  rtl_add(&id_dest->val, &id_src->val, &id_src2->val);  
  rtl_sr(id_dest->reg, &id_dest->val, 4); 
  print_asm_template2(addi);
}

make_EHelper(sltiu) {
  rtl_setrelop(RELOP_LTU, &id_dest->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template2(sltiu);
}

make_EHelper(srai_srli) {
  uint32_t shamt = id_src2->val & 0x1f;
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_shr(&id_dest->val, &id_src->val, &shamt);
      print_asm_template2(srli);
      break;
    case 0b0100000:
      rtl_sar(&id_dest->val, &id_src->val, &shamt);
      print_asm_template2(srai);
      break;
    default:
      Assert(0, "opcode 0010011, funct3 101, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(andi) {
  rtl_and(&id_dest->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template3(andi);
}

make_EHelper(xori) {
  rtl_xor(&id_dest->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template2(xori);
}

make_EHelper(slli) {
  uint32_t shamt = id_src2->val & 0x1f;
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_shl(&id_dest->val, &id_src->val, &shamt);
      print_asm_template2(slli);
      break;
    default:
      Assert(0, "opcode 0010011, funct3 001, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(ori) {
  rtl_or(&id_dest->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template2(ori); 
}

make_EHelper(slti) {
  rtl_setrelop(RELOP_LT, &id_dest->val, &id_src->val, &id_src2->val);
  rtl_sr(id_dest->reg, &id_dest->val, 4);
  print_asm_template2(slti);
}

/* compute因为R-type还需要比较funct7,ps: funct7只有7位 */

make_EHelper(add_sub_mul) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_add(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(add);
      break;
    case 0b0100000:
      rtl_sub(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(sub);
      break;
    case 0b0000001:
      rtl_imul_lo(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(mul);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 000, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(sltu) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_setrelop(RELOP_LTU, &id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(sltu);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 011, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7,cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(xor) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_xor(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(xor);
      break;
    case 0b0000001:
      rtl_idiv_q(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(div);
      break;
    default:
      Assert(0, "opcode 0110011, func3 100, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(or) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_or(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(or);
      break;
    case 0b0000001:
      rtl_idiv_r(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(rem);
      break;
    default:
      Assert(0, "opcode 0110011, func3 110, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(srl_sra_divu) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_shr(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(srl);
      break;
    case 0b0100000:
      rtl_sar(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(sra);
      break;
    case 0b0000001:
      rtl_div_q(&id_dest->val, &id_src->val, &id_src2->val);                
      print_asm_template3(divu);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 101, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(sll_mulh) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_shl(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(sll);
      break;
    case 0b0000001:
      rtl_imul_hi(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(mulh);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 001, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(and_remu) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_and(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(and);
      break;
    case 0b0000001:
      rtl_div_r(&id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template3(remu);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 111, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}

make_EHelper(slt) {
  switch (decinfo.isa.instr.funct7) {
    case 0b0000000:
      rtl_setrelop(RELOP_LT, &id_dest->val, &id_src->val, &id_src2->val);
      print_asm_template2(slt);
      break;
    default:
      Assert(0, "opcode 0110011, funct3 010, funct7=%07o error, pc=0x%08x", decinfo.isa.instr.funct7, cpu.pc);
  }
  rtl_sr(id_dest->reg, &id_dest->val, 4);
}