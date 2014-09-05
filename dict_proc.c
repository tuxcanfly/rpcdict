/*
 * dict_proc.c: dict procedures implementation
 */

#include <stdio.h>
#include "dict.h"

int * insert_1_svc(char **word, struct svc_req *req)
{
    static int result; /* must be static! */
    result = 100;
    return (&result);
}

extern  char ** lookup_1_svc(char **word, struct svc_req *req)
{
    static char *meaning[100];
    strcpy(*meaning, "");
    return meaning;
}
