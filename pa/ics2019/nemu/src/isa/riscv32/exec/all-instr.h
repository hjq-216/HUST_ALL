#include "cpu/decode.h"
#include "cpu/exec.h"

// U-type
make_EHelper(lui);
make_EHelper(auipc);

make_EHelper(ld);
make_EHelper(st);
make_EHelper(lh);
make_EHelper(lb);

make_EHelper(inv);
make_EHelper(nemu_trap);

// computei
make_EHelper(addi);
make_EHelper(sltiu);
make_EHelper(srai_srli);
make_EHelper(andi);
make_EHelper(xori);
make_EHelper(slli);

// compute
make_EHelper(add_sub_mul);
make_EHelper(sltu);
make_EHelper(xor);
make_EHelper(or);
make_EHelper(srl_sra_divu);
make_EHelper(sll_mulh);
make_EHelper(and_remu);
make_EHelper(slt);
make_EHelper(ori);
make_EHelper(slti);

// J-type
make_EHelper(jal);

make_EHelper(jalr);

// B-type
make_EHelper(branch);

// System
make_EHelper(csrrw);
make_EHelper(csrrs);
make_EHelper(ecall);