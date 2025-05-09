/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// dont get paid enough to implement

#include "Instruction.h"

void ori_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "ORI") != 0) {
		// If the op code doesnt match, this isnt the correct command
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

	// This is ORI immediate, so param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is ORI immediate, so param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/* 
		Checking the value of parameters
	*/

	// Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001000");

	// set rt
	setBits_num(20, PARAM1.value, 5);

	// set rs
	setBits_num(25, PARAM2.value, 5);

	// set immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void ori_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	// any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if(checkBits(31, "001101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);	
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting instruction values
	*/

	setOp("ORI");
	// setCond_num(cond);
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination
	setParam(2, REGISTER, Rs); // source register operand
	setParam(3, IMMEDIATE, imm16); // immediate value

	// tell the system that the decoding is done
	state = COMPLETE_DECODE;
}

/*
	Enter Binary:
	> 001101 11001 10000 0000000011111111
	ORI $s0, $t9, #0xFF
*/

/*
	Enter a line of assembly:
	> ORI $s0, $t9, #0xFF
	001000 11001 10000 0000000011111111 
*/