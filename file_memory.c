// when instructions are put into memory - after the assembly
// is converted to machine code, it's kept in a file containing
// an array for the decoded instructions. 16 bits at the start
// represent the origin which is the address in memory the program
// starts executing the routines

#include "memory.h"

void read_image_file(FILE* file) {

	// origin tells us where in memory to place
	// the image file.
	uint16_t origin;
	fread(&origin, sizeof(origin), 1, file);
	
	// swap the origin bits to LSB
	origin = swap16(origin);

	// we have already gathered the info about
	// the maximum file size so we can read it 
	// once
	uint16_t max_read = MEMORY_MAX - origin;
	uint16_t * ptr = memory + origin;
	size_t read = fread(ptr, sizeof(uint16_t), max_read, file);

	// swap to little endian i.e starting with
	// the least signifigant byte of the file.
	// makes it easier for direct translation
	while((read--) > 0) {
		// swap16 is called in order to swap
		// our 16 bits big endian to little endian
		// --> makes sense as I'll be running this
		// on x86 architecture
		*ptr = swap16(*ptr);
		++ptr;
	}
}

// swap function for converting val from 
// big endian to little endian
uint16_t swap16(uint16_t val) {
	return (x << 8) | (x >> 8);
}

// to make it easier - a helper function
// for read_image_file that takes in the path
// to the files location
int read_image(const char* image_path) {

	FILE* file = fopen(image_path, "rb");
	if(!file) {
		return 0;
	}
	
	// on success load it into our function
	// close and return exit success.
	read_image_file(file);
	fclose(file);
	return 1;
}
