#ifndef FILES_H
#define FILES_H
#include <stddef.h>

typedef enum { 
    FILE_OK, FILE_NOT_EXIST, FILE_TOO_LARGE, FILE_READ_ERROR 
} file_errors;

int is_file(const char* path);
char* read_file(const char* f_name, file_errors* err, size_t* f_size);

#endif
