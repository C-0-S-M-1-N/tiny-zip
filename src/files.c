#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "files.h"

int is_file(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

char* read_file(const char* f_name, file_errors* err, size_t* f_size) {
    char* buffer;
    size_t read_length, length;
    FILE* f_input = fopen(f_name, "rb");
    
    if(f_input) {
        fseek(f_input, 0, SEEK_END);
        length = ftell(f_input);
        fseek(f_input, 0, SEEK_SET);
        
        if (length > 1<<30) {
            *err = FILE_TOO_LARGE;
            return NULL;
        }
        
        buffer = (char*)malloc(length + 1);
        
        if (length) {
            read_length = fread(buffer, 1, length, f_input);
            
            if (length != read_length) {
                 free(buffer);
                 *err = FILE_READ_ERROR;
                 return NULL;
            }
        }
        
        fclose(f_input);
        
        *err = FILE_OK;
        buffer[length] = '\0';
        *f_size = length;
    }
    else {
        *err = FILE_NOT_EXIST;
        return NULL;
    }
    
    return buffer;
}