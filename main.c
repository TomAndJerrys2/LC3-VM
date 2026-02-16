include "memory.h"

int main(int argc, char** argv) {
	
	// one condition flag should only be specified at one 
	// given moment, hence we set the z flag
	registers[R_COND] = FL_ZERO;

	// set program counter to start pos
	// 0x3000 is the default address most
	// LC3 binaries start from
	enum { PC_START = 0x3000 };
	registers[R_PC]

	return 0;
}
