#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>

#include <zlib.h>

#include <include/files.h>
#include <include/utils.h>
#include <include/file_record.h>
#include <include/compresser.h>

void compress_file(const char* input, const char* output) {
    FILE* source = fopen(input, "rb");
    FILE* dest = fopen(output, "wb");

    int ret, flush, size=0, old_size=0;
    unsigned have;
    z_stream strm;
    unsigned char temp[CHUNK];
    unsigned char* in = malloc(1000 * CHUNK);

    FILERECORD record = {
        .filename_size = strlen("a"),
        .filename = "a",
        .data = malloc(1000 * CHUNK)
    };

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    ret = deflateInit(&strm, Z_BEST_COMPRESSION);
    ASSERT(ret == Z_OK);

    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            deflateEnd(&strm);
            break;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        old_size += strlen(in);
        
        do {
            strm.avail_out = CHUNK;
            strm.next_out = temp;
            ret = deflate(&strm, flush);
            ASSERT(ret != Z_STREAM_ERROR);
            have = CHUNK - strm.avail_out;

            for(int i=size, j=0; i<size+have; i++, j++) {
                record.data[i] = temp[j];
            }
            record.data[size+have] = '\0';

            size += have;
        } while(strm.avail_out == 0);
    } while(flush != Z_FINISH);

    free(in);
    deflateEnd(&strm);
    
    record.uncompressed_size = old_size;
    record.compressed_size = size;

    serialize_record(dest, &record);

    free(record.data);
    fclose(source);
    fclose(dest);
}

void compress_dir(const char* input, const char* output) {

}
