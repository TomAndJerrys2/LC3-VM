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

// prompt TTY for an input character from stdin
void TRAP_IN_FUNC(void) {

	printf("> Enter a character: ");
	char c = getchar();
	
	// output the character entered to stdout
	putc(c, stdout);
	fflush(stdout);
	// cast the char in R0 to be 16 bits wide
	registers[R_R0] = (uint16_t)(c);

	update_flags(R_R0);
}

// output characters in contiguous memory
// i.e a string lmao
void TRAP_PUTSP_FUNC(void) {
	
	// same logic. we point to the first character
	// in memory, of the string. which is in R0
	uint16_t * character = memory + registers[R_R0];
	
	// while character holds some value
	while(*character) {
		
		// ---------------------------------------------- //
		// notice how usually, especially on my		  //
		// computers architecture which is Intel x86      //
		// when debugging in GDB you'll often see the     //
		// memory locations swapped for multi-byte	  //
		// data types (especially common with strings)    //
		// 						  //
		// this is because the least or LITTLEst byte     //
		// which is at the end is stored first. This is   //
		// because x86 takes advantage of Little endian   //
		// 						  //
		// LC3s architecture - when working with multi    //
		// byte types, takes advantage  of big endian     //
		// which is more intuitive, hence we need to swap //
		// our memory locations around so its correctly   //
		// formatted 					  //
		//  						  //
		// ---------------------------------------------- //
		
		// get the currently pointed to character
		// and compare it against the most signifigant
		// byte
		char char_one = (*character) & 0xFF;
		putc(char1, stdout);
		
		// "advance" the character by shifting it 
		// 8 bits to the right as memory is in hex format
		// the first character is in a byte and so is the next
		// and so on hence the shift
		char char_two = (*character) >> 8;
		
		// if the next byte hold a value
		if(char_two)
			puts(char_two, stdout);

		++character;
	}	
	
	// flush the buffer
	fflush(stdout);
}

void TRAP_HALT_FUNC(void) {
	
	// put halt to stdout, flush the buffer
	// then exit safely
	puts("HALT");
	fflush(stdout);
	
	running = 0;
}
