#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <string.h>
#include <linux/limits.h>

#include "utils.h"
#include "compresser.h"
#include "files.h"

int main(int argc, char* argv[]) {
	ASSERT(argc > 1);
	const char* input = argv[1];
	char output[PATH_MAX];

	for(int i=2; i<argc; i++) {
		if(strcmp("-o", argv[i]) == 0 || strcmp("--output", argv[i]) == 0) {
			strcpy(output, argv[i+1]);
		}
	}

	if(output[0] == '\0') {
		sprintf(output, "%s.tzip", input);
	}

	if(is_file(input)) {
		compress_file(input, output);
	} else {
		compress_dir(input, output);
	}

	return 0;
}
