/*
* rdict.c: dict client
*/

#include <stdio.h>
#include "dict.h"

int main(int argc, char **argv)
{
    CLIENT *clnt;
    int *result;
    char *server;
    char *proc = malloc(sizeof(char) * 128);
    char *word = malloc(sizeof(char) * 128);
    char *insert = "INSERT";
    char *lookup = "LOOKUP";

    server = argv[1];

    printf("Usage: \n1. INSERT <word>\n2. LOOKUP <word>\n\n");
    while (1) {
        printf("Enter procedure (INSERT, LOOKUP): ");
        scanf("%s", proc);
        printf("Enter word: ");
        scanf("%s", word);

        if (!strcmp(proc, insert)) {
            clnt = clnt_create(server, DICTPROG, INSERTVERS, "tcp"); 

            if (clnt == (CLIENT *)NULL) {
                clnt_pcreateerror(server);
                return 1;
            }

            result = insert_1(&word, clnt);
            if (result == (int *)NULL) {
                clnt_perror(clnt, server);
                return 1;
            }

            if (*result == 0) {
                fprintf(stderr, "could not insert %s\n", word);
                return 1;
            }

            clnt_destroy( clnt );
        }
    }
    return 0;
}
