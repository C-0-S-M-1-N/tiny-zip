#ifndef FILE_RECORD_H
#define FILE_RECORD_H
#include <stdio.h>

#define CHUNK 16384

typedef struct {
    unsigned int uncompressed_size;
    unsigned int compressed_size;
    unsigned int filename_size;

    unsigned char* filename;
    unsigned char* data;
} FILERECORD;

void serialize_record(FILE* dest, FILERECORD* record);
void deserialize_record(FILE* source, FILERECORD* record);

#endif
