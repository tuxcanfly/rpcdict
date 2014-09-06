/*
 * dict_proc.c: dict procedures implementation
 */

#include <stdio.h>
#include "dict.h"

#include "hash.c"

int init;
hashtable_t *hashtable = NULL;

hashtable_t * ht_init()
{
    if (!init) {
        hashtable = ht_create(65536);
        init = 1;
    }
    return hashtable;
}

extern  int * insert_1_svc(char *word, char *meaning, struct svc_req *req)
{
    static int result;
    hashtable_t *hashtable = ht_init();
    ht_set(hashtable, word, meaning);
    result = 1;
    return &result;
}

extern  char ** lookup_1_svc(char *word, struct svc_req *req)
{
    char **meaning = malloc(sizeof(char) * 128);
    hashtable_t *hashtable = ht_init();
    *meaning = ht_get(hashtable, word);
    return meaning;
}
