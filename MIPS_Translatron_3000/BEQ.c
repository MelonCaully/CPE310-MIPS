/*
* Author: Ol' Jim
* Editor: Omar
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void beq_immd_assm(void) {
    // Check if the op code matches "BEQ"
    if (strcmp(OP_CODE, "BEQ") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the types of parameters
    */
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /*
        Checking the values of parameters
    */
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /*
        Building the binary instruction
    */

    // Set opcode for BEQ: 000100
    setBits_str(31, "000100");

    // Set Rs (PARAM2)
    setBits_num(25, PARAM2.value, 5);

    // Set Rt (PARAM1)
    setBits_num(20, PARAM1.value, 5);

    // Set offset (immediate)
    setBits_num(15, PARAM3.value, 16);

    state = COMPLETE_ENCODE;
}

void beq_immd_bin(void) {
    // Check if the opcode bits match BEQ: 000100
    if (checkBits(31, "000100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Extracting values from the binary instruction
    */
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t offset = getBits(15, 16);

    /*
        Populating the instruction fields
    */
    setOp("BEQ");
    setParam(1, REGISTER, Rt);       // First register to compare
    setParam(2, REGISTER, Rs);       // Second register to compare
    setParam(3, IMMEDIATE, offset);  // Branch offset

    state = COMPLETE_DECODE;
}

//Results

/*
	Enter Binary:
	> 000100 01101 00000 00000 00000 110100
	BEQ $zero, $t5, #0x34
*/

/*
	Enter a line of assembly:
	> BEQ $zero, $t5, #0x34
	000100 01101 00000 00000 00000 110100
*/