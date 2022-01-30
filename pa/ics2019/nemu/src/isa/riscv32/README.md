- 新增一个指令步骤

    1. 根据手册修改/exec/exec.c中的opcode_table译码表

    2. 根据指令类型编写译码辅助函数：在/include/isa/decode.h中增加make_DHelper的声明，在decode.c中增加make_DHelper的定义

    3. 根据手册编写执行辅助函数：在/all_instr.h中增加make_EHelper的声明，在compute.c或者control.c中增加make_EHelper的定义

    4. 对于R-type，I-type，S-type， B-type的执行函数还需要根据funct3进一步译码，所以在执行这一系列类型的执行函数时需要进一步定义。如load，store需要在/exec/exec.c中增加执行函数。

- 新增指令

    - li: lui+addi

    - auipc

    - addi

    - jal

    - ret: jalr

    - mv: addi

    - sw

    - j: jal

    - add

    - sltu

    - xor

    - or

    - seqz: sltiu

    - sltiu

    - bne

    - beqz: beq

    - beq

    - sub

    - sh

    - lbu,lw,lhu

    - srl

    - sll

    - and

    - not:xori

    - xori

    - ble:bge

    - bge

    - blt

    - mul

    - div

    - rem

    - lb

    - lh

    - slli

    - srli

    - mulh

    - sra

    - remu

    - divu

- 实现klib：stdio.c,string.c