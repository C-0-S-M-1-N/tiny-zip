#include <stdio.h>
#include <sys/time.h>

#include <include/file_record.h>
#include <include/utils.h>

void serialize_record(FILE* dest, FILERECORD* record) {
    ASSERT(dest != NULL);
    ASSERT(record->data != NULL);
    
    const unsigned char magic[] = { 'T', 'Z' }, version = 10;
    
    const unsigned char header[] = {
        magic[0], magic[1], version, //record->uncompressed_size,
        // record->compressed_size, record->filename_size
        // TODO: add to header compressed and uncompressed sizes + filename
    };

    fwrite(header, 1, sizeof(header), dest);
    fwrite(record->data, 1, record->compressed_size, dest);
}

void deserialize_record(FILE* source, FILERECORD* record) {
    
}
