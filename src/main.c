#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>

#include "utils.h"
#include "compresser.h"
#include "decompresser.h"
#include "files.h"

char input_filename[PATH_MAX], output_filename[PATH_MAX];
bool is_quiet, is_decompress;

bool streq(const char* input, const char* op1, const char* op2) {
	return strcmp(input, op1) == 0 || strcmp(input, op2) == 0;
}

int main(int argc, char* argv[]) {
	ASSERT(argc > 1);

	for(unsigned int i=1; i<argc; i++) {
		if(streq(argv[i], "-q", "--quiet")) {
			is_quiet = true;
		} else if(streq(argv[i], "-d", "--decompress")) {
			is_decompress = true;
		} else if(streq(argv[i], "-o", "--output") && i+1 < argc) {
			strncpy(output_filename, argv[i+1], PATH_MAX);
			i++;
			continue;
		} else if(input_filename[0] == '\0' && argv[i][0] != '-') {
			ASSERT(is_file(argv[i]));
			strncpy(input_filename, argv[i], PATH_MAX);
		}
	}

	if(output_filename[0] == '\0') {
		strcpy(output_filename, "file.tzip");
	}

	ASSERT(input_filename[0] != '\0');

	if(!is_decompress) {
		compress_file(input_filename, output_filename);
	} else {
		decompress_file(input_filename, output_filename);
	}

	return 0;
}
