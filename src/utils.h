#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ASSERT(x) if(!(x)) { printf("[ERROR] assert failed at line %d in file %s\n", __LINE__, __FILE__); exit(-1); }

#define NOW() (unsigned long)time(NULL)

#endif