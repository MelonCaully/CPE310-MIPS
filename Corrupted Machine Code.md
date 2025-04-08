# Corrupted Machine Code

<pre>Below is the machine code where there is a single bit flip in the following fields

000000 01001 01010 010'1'0 00000 100000	                       ADD $t2, $t1, $t2 --> ADD $t0, $t1, $t2

001000 01000 01011 0000000000000101                            ADDI $t3, $t0, #0x5

000000 01001 01010 01100 00000 100100                          SUB $t4, $t1, $t2

001100 01110 01101 0000000000001111	-->	Rs field       ANDI $t5, $t6, #0xF

000100 01101 00000 0000000000110100                            BEQ $zero, $t5, #0x34

000101 01011 01101 0000000000110100                            BNE $t5, $t3, #0x34

000000 01110 01000 00000 00000 011010                          DIV $t0, $t6

000000 00000 000'1'0 01111 00000 010000	                       ERROR --> MFLO $t7

000000 00000 00000 11000 00000 010010                          MFHI $t8

000000 01001 01010 00000 00000 011000                          MULT $t1, $t2

000000 01011 01100 11001 00000 100001	-->	Funct field    ERROR

00110111001100000000000011111111                               ERROR

000000 01000 01001 10001 00000 101010                          SLT $s1, $t0, $t1

00101001000100100000000000001010                               ERROR

00000001001010101001100000100010                               ERROR

001111 00000 10111 0100000000000000                            LUI $s7, $zero, #0x4000

100011 10111 10100 0000000000000000                            LW $s4, #0x0($s7)

10'0'011 10111 10101 0000000000000100	                       LW $s5, #0x4($s7) --> SW $s5, #0x4($s7)

001111 00000 10110 0001001000110100                            LUI $s6, $zero, #0x1234 

<pre>

Resource on Machine Instructions: <https://learn.zybooks.com/zybook/WVUCPE310HefeidaSpring2025/chapter/3/section/5?content_resource_id=56179112>