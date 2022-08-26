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
#include "utils.h"

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
        unsigned int magic_number = 0x69, version = 10, compression_type = Z_BEST_COMPRESSION, compressed_size, uncompressed_size;

        z_stream defstream;
        defstream.zalloc = Z_NULL;
        defstream.zfree = Z_NULL;
        defstream.opaque = Z_NULL;

        defstream.avail_in = (uInt)strlen(f_data)+1;
        defstream.next_in = (Bytef *)f_data;
        defstream.avail_out = (uInt)sizeof(compressed_buffer);
        defstream.next_out = (Bytef *)compressed_buffer;
        
        deflateInit(&defstream, compression_type);
        deflate(&defstream, Z_FINISH);
        deflateEnd(&defstream);

        FILE* output_file = fopen(output, "wb");
        
        uncompressed_size = strlen(f_data);
        compressed_size = strlen(compressed_buffer);
        const unsigned char header[] = { magic_number, version, compression_type, compressed_size, uncompressed_size };

        fwrite(header, 5, 1, output_file);
        fwrite(compressed_buffer, strlen(compressed_buffer), 1, output_file);

        free(f_data);
    }
}

void compress_dir(const char* input, const char* output) {

}

void decompress_file(const char* input, const char* output) {
    file_errors err;
    size_t f_size;
    char* f_data = read_file(input, &err, &f_size);

    if (err != FILE_OK) {
        printf("error opening the input file!\n");
        exit(-1);
    }
    else {
        char decompressed_buffer[2560000];
        unsigned int magic_number = 0x69, version = f_data[1], compression_type = f_data[2];
        unsigned int compressed_size = f_data[3], uncompressed_size = f_data[4];

        printf("version: %d\ncompressed size: %d\nuncompressed size: %d\n", version, compressed_size, uncompressed_size);
        ASSERT(f_data[0] == magic_number);

        z_stream infstream;
        infstream.zalloc = Z_NULL;
        infstream.zfree = Z_NULL;
        infstream.opaque = Z_NULL;

        infstream.avail_in = (uInt)(strlen(f_data)-5);
        infstream.next_in = (Bytef*)(f_data+5);
        infstream.avail_out = (uInt)sizeof(decompressed_buffer);
        infstream.next_out = (Bytef*)decompressed_buffer;
        
        inflateInit(&infstream);
        inflate(&infstream, Z_NO_FLUSH);
        inflateEnd(&infstream);

        FILE* output_file = fopen(output, "wb");
        fwrite(decompressed_buffer, strlen(decompressed_buffer), 1, output_file);

        fclose(output_file);
        free(f_data);
    }
}
// TODO: split everything in chunks https://github.com/madler/zlib/blob/master/examples/zpipe.c
// atm it only works with files smaller than 256 chars
void decompress_dir(const char* input, const char* output) {

}
