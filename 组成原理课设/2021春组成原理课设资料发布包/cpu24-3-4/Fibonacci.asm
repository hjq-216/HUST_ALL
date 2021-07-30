#bltz ����    С��0��ת   �ۼ����㣬�Ӹ�����ʼ�������� revise date:2018/3/12 tiger  
#�������0xfffffff1 0xfffffff2 0xfffffff3 0xfffffff4 0xfffffff5 0xfffffff6 0xfffffff7 0xfffffff8 0xfffffff9 0xfffffffa 0xfffffffb 0xfffffffc 0xfffffffd 0xfffffffe 0xffffffff
.text
#addi $s2,$zero,0
#addi $s3,$zero,1

InitLoop:

addi $s0,$zero,0

fibo:

addi $s1,$zero,$30      #��ʼֵ
addi $30,$s7,$30
addi $s7,$zero,$s1

add $a0,$30,$s3          
addi $v0,$0,34         
syscall                  #�����ǰֵ

bne $s0,$zero, fibo
sub $s4,$s4,$s5
bne $s4,$zero, InitLoop


addi   $v0,$zero,10    
syscall                  #��ͣ���˳�
