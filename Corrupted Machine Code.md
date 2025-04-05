# Corrupted Machine Code

Below is the machine code where there is a single bit flip in the following fields

000000 01001 01010 01010 00000 100000	\-\>	Rd field       ADD $t2, $t1, $t2

00100001000010110000000000000101                               ADDI $t3, $t0, #0x5

00000001001010100110000000100100                               SUB $t4, $t1, $t2

00110001110011010000000000001111	\-\>	Rs field           ANDI $t5, $t6, #0xF

00010001101000000000000000110100                               BEQ $zero, $t5, #0x34

00010101011011010000000000110100                               BNE $t5, $t3, #0x34

000000 01110 01000 00000 00000 011010                          DIV $t0, $t6

000000 00000 000'1'0 01111 00000 010000	\-\>	Rt field       ERROR \-\> MFLO $t7

000000 00000 00000 11000 00000 010010                          MFHI $t8

000000 01001 01010 00000 00000 011000                          MULT $t1, $t2

00000001011011001100100000100001	\-\>	Funct field        ERROR

00110111001100000000000011111111                               ERROR

00000001000010011000100000101010                               SLT $s1, $t0, $t1

00101001000100100000000000001010                               ERROR

00000001001010101001100000100010                               ERROR

00111100000101110100000000000000                               LUI $s7, $zero, #0x4000

10001110111101000000000000000000                               LW $s4, #0x0($s7)

10001110111101010000000000000100	\-\>	opcode field       LW $s5, #0x4($s7)

00111100000101100001001000110100                               LUI $s6, $zero, #0x1234

Resource on Machine Instructions: <https://learn.zybooks.com/zybook/WVUCPE310HefeidaSpring2025/chapter/3/section/5?content_resource_id=56179112>