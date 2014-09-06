/*
 * rdict.c: dict client
 * usage: ./rdict localhost
 */

#include <stdio.h>
#include "dict.h"

int main(int argc, char **argv)
{
    CLIENT *clnt;
    int *result;
    char *server;

    /*
     * initialize variables for reading procedure, word, meaning
     * and values to compare procedure name against
     */
    char *proc = malloc(sizeof(char) * 128);
    char *word = malloc(sizeof(char) * 128);
    char *meaning = malloc(sizeof(char) * 128);
    char *insert = "INSERT";
    char *lookup = "LOOKUP";

    /*
     * first argument is the RPC server to connect to
     */
    server = argv[1];

    clnt = clnt_create(server, DICTPROG, DICTVERS, "tcp"); 
    if (clnt == (CLIENT *)NULL) {
        clnt_pcreateerror(server);
        return 1;
    }

    printf("Usage: \n1. INSERT <word>\n2. LOOKUP <word>\n\n");

    /*
     * interactive mode:
     * keep accepting user input and processing procedures
     * user can exit by sending Ctrl+C
     */
    while (1) {
        printf("Enter procedure (INSERT, LOOKUP): ");
        scanf("%s", proc);

        if (!strcmp(proc, insert)) {
            // call INSERT procedure
            printf("Enter word: ");
            scanf("%s", word);

            printf("Enter meaning: ");
            scanf("%s", meaning);

            result = insert_1(word, meaning, clnt);
            if (result == (int *)NULL) {
                clnt_perror(clnt, server);
                return 1;
            }

            if (*result == 0) {
                fprintf(stderr, "could not add '%s' to the dictionary\n", word);
            } else if (*result == 1) {
                printf("sucessfully added '%s' to the dictionary\n", word);
            }
        } else if (!strcmp(proc, lookup)) {
            // call LOOKUP procedure
            printf("Enter word: ");
            scanf("%s", word);

            meaning = *lookup_1(word, clnt);

            if (!strcmp(meaning, "")) {
                fprintf(stderr, "could not get meaning of '%s' from the dictionary\n", word);
            } else {
                printf("sucessfully got meaning of '%s' from the dictionary: %s\n", word, meaning);
            }
        } else {
            // unknown procedure
            printf("Invalid procedure, please enter INSERT or LOOKUP\n");
        }
    }
    clnt_destroy( clnt );
    return 0;
}
