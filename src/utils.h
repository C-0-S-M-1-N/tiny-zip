#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(x) if(!(x)) { printf("assert failed at line %d in file %s\n", __LINE__, __FILE__); exit(-1); }

#endif