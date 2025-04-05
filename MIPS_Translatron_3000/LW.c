#include "Instruction.h"

void lw_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
		// If the op code does not match, then the command is wrong
		state = WRONG_COMMAND;
		return;
	}
	
	/*
		Checking the type of parameters
	*/
	
	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be an immediate value
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	// The third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// immediate value should be 16 bits
	if ( PARAM2.value > 0x7FFF) {
		state = INVALID_IMMED;
		return;
	}
	
	// rt should be 31 or less
	if ( PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}


	// set opcode
	setBits_str(31, "100011");

	// set rs
	setBits_num(20, PARAM1.value, 5);

	// set immediate
	setBits_num(15, PARAM2.value, 16);

	// set rt
	setBits_num(25, PARAM3.value, 5);

	// tell the system that the encoding is done
	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	// any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code matches, then the rest can be read as correctly

	/*
		Finding the values of the parameters
	*/
	
	// getBits(start_bit, width)
	//ERROR FIX: The order of Rs, Rt, and offset was changed to match the correct order of Rs, Rt, and offsetQ
	uint32_t Rs = getBits(20, 5);
	uint32_t Rt = getBits(25, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("LW");
	// setCond_num(cond);
	// setParam(param_num, param_type, param_value)
	// Error Fix: The order of Rs, Rt, and offset was changed to match the correct order of Rs, Rt, and offsetQ
	setParam(1, REGISTER, Rs);
	setParam(3, REGISTER, Rt);
	setParam(2, IMMEDIATE, imm16);

	// tell the system that the decoding is done
	state = COMPLETE_DECODE;

}


// Results

/*
	Enter Binary:
	> 100011 10111 10100 0000000000000000
	LW $s4, #0x0($s7)
*/

/*
	Enter a line of assembly:
	> LW $s4, #0x0($s7)
	100011 10111 10100 0000000000000000 
*/