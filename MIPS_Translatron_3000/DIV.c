/*
* Author: Ol' Jim
* Debugging/Documentation: Malone Ingham
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void div_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "DIV") != 0) {
		// If the op code does not match, then the command is wrong
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is DIV register, so param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "000000");

	// set the funct
	setBits_str(5, "011010");

	// set rs
	setBits_num(20, PARAM1.value, 5);

	// set rt
	setBits_num(25, PARAM2.value, 5);

	//setBits_num(15, 0, 10);
	
	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	// any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(20, 5);
	uint32_t Rt = getBits(25, 5);

	setOp("DIV");
	// setCond_num(cond);
	// setParam(param_num, param_type, param_value)
	// ERROR FIX: Registers were originilly swapped. Rs is now the destination register and Rt is the source register.
	setParam(1, REGISTER, Rs); // destination
	setParam(2, REGISTER, Rt); // source register operand

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}

// Results

/*
	Enter Binary:
	> 000000 01000 01110 00000 00000 011010 
	DIV $t0, $t6
*/

/*
	Enter a line of assembly:
	> DIV $t0, $t6
	000000 01000 01110 00000 00000 011010
*/