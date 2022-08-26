#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#include <zlib.h>

#include "compresser.h"
#include "files.h"

void compress_file(const char* input, const char* output) {
    file_errors err;
    size_t f_size;
    char* f_data = read_file(input, &err, &f_size);

    if (err) {
        printf("error opening the input file!\n");
        exit(-1);
    }
    else {
        char compressed_buffer[256];

        z_stream defstream;
        defstream.zalloc = Z_NULL;
        defstream.zfree = Z_NULL;
        defstream.opaque = Z_NULL;

        defstream.avail_in = (uInt)strlen(f_data)+1;
        defstream.next_in = (Bytef *)f_data;
        defstream.avail_out = (uInt)sizeof(compressed_buffer);
        defstream.next_out = (Bytef *)compressed_buffer;
        
        deflateInit(&defstream, Z_BEST_COMPRESSION);
        deflate(&defstream, Z_FINISH);
        deflateEnd(&defstream);
        
        FILE* output_ptr = fopen(output, "wb");
        fwrite(compressed_buffer, strlen(compressed_buffer), 1, output_ptr);
        
        free(f_data);
    }
}

void compress_dir(const char* input, const char* output) {

}
