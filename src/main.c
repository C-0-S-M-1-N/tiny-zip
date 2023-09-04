#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>

#include <utils.h>
#include <compresser.h>
#include <decompresser.h>
#include <files.h>

char input_filename[PATH_MAX], output_filename[PATH_MAX];
bool is_quiet;

bool streq(const char* input, const char* op1, const char* op2) {
	return strcmp(input, op1) == 0 || strcmp(input, op2) == 0;
}


unsigned GetFlags(const int argc, char* argv[]){
	unsigned ret = 0;
	for(int i = 1; i < argc; i++){
		if(argv[i][0] != '-'){
			if(ret & OUTPUT){
				ret ^= OUTPUT;
				snprintf(output_filename, MAX_INPUT, "%s", argv[i]);
			} else if(!(ret & INPUT)){
				ret |= INPUT;
				snprintf(input_filename, MAX_INPUT, "%s", argv[i]);
			} else {
				fprintf(stderr, "W: Unknown garbage value `%s`\n", argv[i]);
			}
			continue;
		}
		
		for(int j = 1; argv[i][j]; j++){
			if(argv[i][j] == '-'){
				if(!strcmp(argv[i]+j+1, "output")) ret |= OUTPUT;
				else if(!strcmp(argv[i]+j+1, "quiet")) ret |= QUIET;
				else if(!strcmp(argv[i]+j+1, "decompress")) ret |= DECOMPRESS;
				else {fprintf(stderr, "E: Unknown flag `%s`\n", argv[i]); exit(EXIT_FAILURE);}
				break;
			}
			switch(argv[i][j]){
			case 'o': ret |= OUTPUT; 		break;
			case 'q': ret |= QUIET;  		break;
			case 'd': ret |= DECOMPRESS; 	break;
			default: fprintf(stderr, "E: Unknown flag `-%c`\n", argv[i][j]); 
					 exit(EXIT_FAILURE); 	break;
			}
		}
	}
	return ret;
}

int main(int argc, char* argv[]) {
	ASSERT(argc > 1);

	unsigned flags = GetFlags(argc, argv);
	
	if(flags & QUIET) is_quiet = 1;
// 	printf("%hx", (unsigned short)flags);
	fprintf(stderr, "inp: %s\n out: %s\n", input_filename, output_filename);
	if(output_filename[0] == '\0') {
		snprintf(output_filename, MAX_INPUT, "file.tzip");
	}

	if(!(flags & INPUT)){
		fprintf(stderr, "E: no input file\n");
		return EXIT_FAILURE;
	}
	
	if(flags & DECOMPRESS){
		decompress_file(input_filename, output_filename);
		return EXIT_SUCCESS;
	}
	compress_file(input_filename, output_filename);

	return EXIT_SUCCESS;
}
