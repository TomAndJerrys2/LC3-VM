#include "memory.h"

#include <stdio.h>

int main(int argc, char** argv) {

	// Loads argument paths for VM images
	if(argc < 2) {
		printf("> LC3 [IMAGE_FILE1], [IMAGE_FILE2] ...\n");
		exit(2);
	}

	for(size_t j = 1; j < argc; ++j) {
		if(!read_image(argv[j])) {
			printf("> Failed to load Image File: %s\n", 
					argv[j]);

			exit(1);
		}
	}

	// one condition flag should only be specified at one 
	// given moment, hence we set the z flag
	registers[R_COND] = FL_ZERO;

	// set program counter to start pos
	// 0x3000 is the default address most
	// LC3 binaries start from
	enum { PC_START = 0x3000 };
	registers[R_PC];

	int running = 1;
	while(running) {
		
		// fetch instruction
		uint16_t input_str = mem_read(registers[R_PC]++);
		uint16_t output = input_str >> 12;
		
		// based on output (input shifted to the right
		// by 12 bits as described in header)
		switch(output) {
			case OP_ADD:
				OP_ADD_FUNC();
				break;

			case OP_AND:
				OP_AND_FUNC();
				break;

			case OP_NOT:
				OP_NOT_FUNC();
				break;

			case OP_BR:
				OP_BR_FUNC();
				break;

			case OP_JMP:
				OP_JMP_FUNC();
				break;

			case OP_LD:
				OP_LD_FUNC();
				break;

			case OP_JSR:
				OP_JSR_FUNC();
				break;

			case OP_LDI:
				OP_LDI_FUNC();
				break;

			case OP_LDR:
				OP_LDR_FUNC();
				break;

			case OP_LEA:
				OP_LEA_FUNC();
				break;

			case OP_ST:
				OP_ST_FUNC();
				break;

			case OP_STI:
				OP_STI_FUNC();
				break;

			case OP_STR:
				OP_STR_FUNC();
				break;

			case OP_TRAP:
				OP_TRAP_FUNC();
				break;

			case OP_RES:
			case OP_RTI:
			default:
				BAD_OP_CODE();
				break;
		}	
	}
	
	SHUTDOWN();
}
