/*
 * dict_proc.c: dict procedures implementation
 * usage: ./dict_server
 */

#include <stdio.h>
#include "dict.h"

#include "hash.c"

/*
 * init - whether hashtable is initialized
 */
int init;

/*
 *  hashtable - hashtable to insert and retreive by word
 */
hashtable_t *hashtable = NULL;

/*
 * ht_init - initialize hashtable if required and return it's pointer
 * return an initialized hashtable if already intialized
 */
hashtable_t * ht_init()
{
    if (!init) {
        hashtable = ht_create(65536);
        init = 1;
    }
    return hashtable;
}

/*
 * insert_1_svc - insert into the hashtable
 * key - word
 * value - meaning
 */
extern  int * insert_1_svc(char *word, char *meaning, struct svc_req *req)
{
    static int result;
    hashtable_t *hashtable = ht_init();
    ht_set(hashtable, word, meaning);
    result = 1;
    return &result;
}

/*
 * lookup_1_svc - lookup the word and return it's meaning
 */
extern  char ** lookup_1_svc(char *word, struct svc_req *req)
{
    char **meaning = malloc(sizeof(char) * 128);
    hashtable_t *hashtable = ht_init();
    *meaning = ht_get(hashtable, word);
    if (*meaning == NULL) {
        *meaning = "";
    }
    return meaning;
}
