#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT(x) if(!(x)) { printf("[ERROR] assert failed at line %d in file %s\n", __LINE__, __FILE__); exit(-1); }

#define NOW() (unsigned long)time(NULL)

// flags
#define QUIET 0b00000001
#define DECOMPRESS 0b00000010
#define OUTPUT 0b00000100 // yes even this
#define INPUT 0b000001000

#endif
