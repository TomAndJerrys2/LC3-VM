#include "memory.h"

// adding to register values
void OP_ADD_FUNC(void) {

	// destination register - DR
	uint16_t reg0 = (input_str >> 9) & 0x7;

	// first operand in 16 bit addr i.e SR1
	uint16_t reg1 = (input_str >> 6) & 0x7;

	// check whether we are in immediate mode
	uint16_t imm_flag = (input_str >> 5) & 0x1;
	
	// if in immediate mode, we expand the 5 bits and add
	// the pre-stored value to a given register
	if(imm_flag) {
		uint16_t imm5 = SIGN_EXTEND(input_str & 0x1F, 5);
		registers[reg0] = registers[reg1] + imm5;
	}
	// in register mode
	else {
		uint16_t reg2 = input_str & 0x7;
		registers[reg0] = registers[reg1] + registers[reg2];	
	}

	update_flags(reg0);
}

// load indirect function for grabbing a value
// from memory via the data bus
void OP_LDI_FUNC(void) {
	
	// destination register - DR
	uint16_t reg0 = (input_str >> 9) & 0x7;

	// extend the offset program counter by 9 bits
	uint16_t pc_offset = SIGN_EXTEND(input_str & 0x1FF, 9);

	// add the offset to the current PC, read the memory address
	// to return the final location
	registers[reg0] = mem_read(mem_read(R_PC) + pc_offset);
	update_flags(reg0);
}

// Bitwise AND
void OP_AND_FUNC(void) {
	
	// destination register - DR
	uint16_t reg0 = (input_str >> 9) & 0x7;

	// first operand to compare from register
	uint16_t reg1 = (input_str >> 6) & 0x7;

	// Immediate mode flag checks
	uint16_t imm_flag = (input_str >> 5) & 0x1;
	if(imm_flag) {
		uint16_t imm5 = SIGN_EXTEND(input_str & 0x1F, 5);
		
		// if immediate mode, compare reg1 with the pre-stored
		// value in the 5 bit allocated space for immediate mode
		registers[reg0] = registers[reg1] & imm5;
	}
	// register mode
	else {
		uint16_t reg2 = input_str & 0x7;
		registers[reg0] = registers[reg1] & registers[reg2];
	}

	update_flags(reg0);
}

// Bitwise NOT
void OP_NOT_FUNC(void) {
	
	// Destination Register
	uint16_t reg0 = (input_str >> 9) & 0x7;
	
	// value operand is inversed to represent NOT
	uint16_t reg1 = (input_str >> 6) & 0x7;

	registers[reg1] = ~registers[reg1];
	update_flags(reg0);
}

// Branch instruction 
void OP_BR_FUNC(void) { 
	
	uint16_t pc_offset = SIGN_EXTEND(input_str & 0x1FF, 9);

	uint16_t cond_flag = (input_str >> 8) & 0x7;
	
	// comparing the condition flag with the condition
	// flag registers value via bitwise AND
	if(cond_flag & registers[R_COND]) {
		registers[R_PC] += pc_offset;
	}
}

// Jump instruction
void OP_JMP_FUNC(void) {
	// also handles RET as RET is a special case of
	// the jump instruction whenever reg1 is 7
	uint16_t reg1 = (input_str >> 6) & 7;

	registers[R_PC] = registers[reg1];	
}

// Unlike Jump which handles the "Jumping" of 
// instructions JSR jumps to a different register 
// via an offset
void OP_JSR_FUNC(void) {
	
	uint16_t long_flag = (input_str >> 11) & 1;

	registers[R_R7] = registers[R_PC};
	if(long_flag) {
		uint16_t long_pc_offset = SIGN_EXTEND(input_str & 0x7FF, 11);
		registers[R_PC] += long_pc_offset;
	}

	else {
		uint16_t registers[R_PC] = registers[R1];
	}
}

// Load instruction
void OP_LOAD_FUNC(void) {
	
	uint16_t reg0 = (input_str >> 9) & 0x7;
	uint16_t pc_offset = SIGN_EXTEND(input_str & 0x1FF, 9);

	registers[reg0] = mem_read(registers[R_PC] + pc_offset);
	update_flags(reg0);
}

// Load Register
void OP_LDR_FUNC(void) {
	
	uint16_t reg0 = (input_str >> 9) & 0x7;
	uint16_t reg1 = (input_str >> 6) & 0x7;

	uint16_t offset = SIGN_EXTEND(input_str & 0x3F, 6);
	registers[reg0] = mem_read(registers[reg1] + offset);
	update_flags(reg0);
}

// Load effective address
void OP_LEA_FUNC(void) {

	uint16_t reg0 = (input_str >> 9) & 0x7;
	uint16_t pc_offset = SIGN_EXTEND(input_str & 0x1FF, 9);

	registers[reg0] = registers[R_PC] + pc_offset;
	update_flags(reg0);
}
