// Using LC3s native memory allocation space
// which is based around 16bit architecture
#define MEMORY_MAX (1 << 16) 
uint16_t memory[MEMORY_MAX]

// LC3 has 10 registers - which isn't that big
// but this is granted due to its explicit reduction
// in the instruction set
enum {
	
	// seven general purpose registers
	R_R0 = 0,
	R_R1,
	R_R2,
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,

	// 1 conitional flag register
	R_COND,

	// 1 Program counter register
	R_COUNT
};

// store the register values in an array
uint16_t registers[R_COUNT];

// 16 Op codes for LC3 - each are 12 + 4 bits
// where the left 4 bits are used to store the code
// and the right 12 bits will store parameters
enum {
	
	OP_BR = 0, // branch
	OP_ADD,    // add
	OP_LD,     // load
	OP_ST,     // store
	OP_JSR,    // Jump register
	OP_AND,    // bitwise AND
	OP_LDR,    // load register
	OP_STR,    // store register
	OP_RTI,    // unused
	OP_NOT,    // bitwise NOT
	OP_LDI,    // load indirect
	OP_STI,    // store indirect
	OP_JMP,    // jump
	OP_RES,    // reserved --> unused
	OP_LEA,    // load effective address
	OP_TRAP    // execute trap
};

// condition flags for logic and control flow
// LC-3 only has three and evluates logic
// based on the sign of the previous calc
enum {
	FL_POS = 1 << 0; // +ve
	FL_ZRO = 1 << 0; // zero
	FL_NEG = 1 << 2; // -ve
};


