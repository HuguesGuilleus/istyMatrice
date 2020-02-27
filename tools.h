// 2020 GUILLEUS Hugues IATIC3 <hugues.guilleus@ens.uvsq.fr>

#ifndef TOOLS
#define TOOLS

#include <stdio.h>

void clearStdin(void);

typedef int bool;
#define TRUE 1
#define FALSE 0

#define TRACE(ms)                                                              \
	fprintf(stderr, "\n\e[1;43m%s:%d\e[0;49m \e[1;31m%s\e[0m\n", __FILE__,        \
	        __LINE__, ms)

#endif
