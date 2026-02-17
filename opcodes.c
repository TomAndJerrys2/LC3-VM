#include "memory.h"

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
