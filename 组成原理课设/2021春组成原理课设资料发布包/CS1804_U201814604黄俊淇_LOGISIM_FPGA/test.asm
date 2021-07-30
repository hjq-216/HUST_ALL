.text


 
InteruptProgram1:

###

addi $s6,$zero,1       #中断?1,2,3   不同中断号显�?????�?????
addi $s1,$zero,0
addi $s2,$zero,1
add $s4,$zero,$t6      #循环次数初始?  
addi $s5,$zero,1       #计数器累�?????

IntLoop1:
add $s0,$zero,$s6   

IntLeftShift1:       
add $s3,$s1,$s2
add $s1,$zero,$s2
add $s2,$zero,$s3


add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   

#bne $s0, $zero, IntLeftShift1
sub $s4,$s4,$s5      #循环次数递减
bne $s4, $zero, IntLoop1

addi   $v0,$zero,10         # system call for exit   
syscall                  # we are out of here. 
eret
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   
