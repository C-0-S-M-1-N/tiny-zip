#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#include <zlib.h>

#include <compresser.h>
#include <files.h>
#include <utils.h>
#include <file_record.h>

void decompress_file(const char* input, const char* output) {
    FILE* source = fopen(input, "rb");
    FILE* dest = fopen(output, "wb");

    unsigned char header[3];
    fread(header, 1, sizeof(header), source);
    printf("magic: %c%c, version: %d\n", header[0], header[1], header[2]);

    int ret;
    unsigned have;
    z_stream strm;
    unsigned char* in = malloc(1000 * CHUNK);
    unsigned char* out = malloc(1000 * CHUNK);

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    ret = inflateInit(&strm);
    ASSERT(ret == Z_OK);

    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            inflateEnd(&strm);
            break;
        }
        if(strm.avail_in == 0)
            break;
        strm.next_in = in;
        
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            ASSERT(ret != Z_STREAM_ERROR);

            switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    return;
            }

            have = CHUNK - strm.avail_out;
            if(fwrite(out, 1, have, dest) != have || ferror(dest)) {
                inflateEnd(&strm);
                return;
            }
        } while(strm.avail_out == 0);
    } while(ret != Z_STREAM_END);

    free(in);
    free(out);
    inflateEnd(&strm);

    fclose(source);
    fclose(dest);
}

void decompress_dir(const char* input, const char* output) {

}
