registers[R_R7] = registers[R_PC];

// each corrosponding trap routine will be
// implemented into a C function for now, 
// however - I am curious about a true LC3
// implementation which is usually done in
// assembly
switch(input_str & 0xFF) {

	case TRAP_GETC:
		TRAP_GETC_FUNC();
		break;

	case TRAP_OUT:
		TRAP_OUT_FUNC();
		break;

	case TRAP_PUTS:
		TRAP_PUTS_FUNC();
		break;

	case TRAP_IN:
		TRAP_IN_FUNC();
		break;

	case TRAP_PUTSP:
		TRAP_PUTSP_FUNC();
		break;

	case TRAP_HALT:
		TRAP_HALT_FUNC();
		break;
}

// Trap PUTS is used to ouput a null-terminated
// string, it point to the first character of said
// string in a given register i.e R0
void TRAP_PUTS_FUNC(void) {

	// the pointer here stores a 16 bit wide char
	// which is converted via the memory buffer
	// + the register we are storing the first char
	uint16_t * character = memory + registers[R_R0];
	
	// while character holds some value
	while(*character) {
		// put the casted character to the standard output
		puts((char)(*character), stdout);
		++c;
	}
	
	// flush the stdout buffer once we have finished
	// iterating over each character in memory
	fflush(stdout);
}

// store a single character into a register
void TRAP_GETC_FUNC(void) {
	
	// get some arbitrary register and 
	// assign it to the input buffer returned from
	// getchar and cast said input to 16 bits so its
	// storeable in our 16 bit registers
	registers[R_R0] = (uint16_t)getchar();
	
	// update the flags on R0 to specify its holding
	// a character
	update_flags(R_R0);
}

// output a single character
void TRAP_OUT_FUNC(void) {

	// feed a single character (appropriately from R0)
	// into the stdout buffer
	putc((char)registers[R_R0], stdout);

	// flush the stdout buffer once we are done!
	fflush(stdout);
}
