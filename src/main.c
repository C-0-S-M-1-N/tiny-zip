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
bool is_quiet, is_decompress;

bool streq(const char* input, const char* op1, const char* op2) {
	return strcmp(input, op1) == 0 || strcmp(input, op2) == 0;
}

unsigned GetFlags(const int argc, char* argv[]){ // update type if more than 8 flags
	unsigned ret = 0;
	for(int i = 0; i < argc; i++){
		if(argv[i][0] == '-' && argv[i][1] != '-'){
			for(int j = 2; argv[i][j]; j++){
				switch(argv[i][j]){
					case 'q': ret |= QUIET;	break;
					case 'd': ret |= DECOMPRESS; break;
					case 'o': ret |= OUTPUT; break;
					default: fprintf(stderr, "Unknown flag `%c`\n", argv[i][j]); exit(EXIT_FAILURE);
				}
			}
			if(!(ret & OUTPUT)) continue;
			if(i+1 >= argc){
				fprintf(stderr, "No output file provided after -o flag\n"); 
				exit(EXIT_FAILURE);
			}
			snprintf(output_filename, PATH_MAX, "%s", argv[i+1]);
		} else if(argv[i][0] == '-' && argv[i][1] == '-'){
			if(!strcmp(argv[i]+2, "quiet")) ret |= QUIET;
			else if(!strcmp(argv[i]+2, "decompress")) ret |= DECOMPRESS;
			else if(!strcmp(argv[i]+2, "output")){
				ret |= OUTPUT;
												   
				if(i+1 >= argc){
					printf("No output file provided after -o flag\n"); 
					exit(EXIT_FAILURE);
				}
				snprintf(output_filename, PATH_MAX, "%s", argv[i+1]);
				
			} else {
				fprintf(stderr, "Unknown flag `%s`", argv[i]);
			}
		} else if(!(ret & INPUT)){
			ret |= INPUT;
			snprintf(input_filename, PATH_MAX, "%s", argv[i]);
		} else {
			fprintf(stderr, "W: Unknown garbage alongside command arguments `%s`\n", argv[i]);
		}
	}
	return ret;
}

int main(int argc, char* argv[]) {
	ASSERT(argc > 1);

	unsigned flags = GetFlags(argc, argv);
	
	if(flags & QUIET) is_quiet = 1;

	if(output_filename[0] == '\0') {
		snprintf(output_filename, MAX_INPUT, "file.tzip");
	}

	ASSERT(input_filename[0] != '\0');
	
	if(flags & DECOMPRESS){
		decompress_file(input_filename, output_filename);
		return EXIT_SUCCESS;
	}
	compress_file(input_filename, output_filename);

	return EXIT_SUCCESS;
}
