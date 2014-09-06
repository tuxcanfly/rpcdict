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
    char *meaning = malloc(sizeof(char) * 128);
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
            printf("Enter meaning: ");
            scanf("%s", meaning);

            clnt = clnt_create(server, DICTPROG, DICTVERS, "tcp"); 

            if (clnt == (CLIENT *)NULL) {
                clnt_pcreateerror(server);
                return 1;
            }

            result = insert_1(word, meaning, clnt);
            if (result == (int *)NULL) {
                clnt_perror(clnt, server);
                return 1;
            }

            if (*result == 100) {
                printf("sucessfully added '%s' to the dictionary\n", word);
            }

            if (*result == 0) {
                fprintf(stderr, "could not insert %s\n", word);
                return 1;
            }

            clnt_destroy( clnt );
        }
        else if (!strcmp(proc, lookup)) {
            clnt = clnt_create(server, DICTPROG, DICTVERS, "tcp"); 

            if (clnt == (CLIENT *)NULL) {
                clnt_pcreateerror(server);
                return 1;
            }

            meaning = *lookup_1(word, clnt);
            if (result == (int *)NULL) {
                clnt_perror(clnt, server);
                return 1;
            }

            printf("sucessfully got meaning of '%s' from the dictionary: %s\n", word, meaning);

            clnt_destroy( clnt );
        }
    }
    return 0;
}
