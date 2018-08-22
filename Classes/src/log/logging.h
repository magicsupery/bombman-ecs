#ifndef _H_LOGGING_H_
#define _H_LOGGING_H_
#include <stdio.h>

namespace ecs
{
#define BOMBLOG(...) {\
	fprintf(stderr,"%s:line %d:\t",__FILE__,__LINE__);\
	fprintf(stderr,__VA_ARGS__);\
	fprintf(stderr,"\n");\
}

}
#endif
