#ifndef _COMMON_H
#define _COMMON_H

#define OK			(1)
#define ERROR		(0)
#define INFEASIBLE	(-1)
#define OVERFLOW	(-2)

#define TRUE		(1 == 1)
#define FALSE		(!TRUE)

typedef int status;

#ifdef INT_TYPE
#include "integer.h"
typedef int Elemtype;
#endif

#ifdef CHAR_TYPE
#include "char.h"
typedef char Elemtype;
#endif

#ifdef STRUCT_TYPE
#include "struct.h"
#define DATA_INT

typedef struct node Elemtype;

#endif

#ifdef STRING_TYPE
typedef char * Elmetype;
#endif

#endif 	/* _COMMON_H */
