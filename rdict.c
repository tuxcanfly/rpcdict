/*
 * rdict.c: dict client
 * usage: ./rdict localhost
 */

#include <stdio.h>
#include "dict.h"

#define MAX_PROC_SIZE sizeof(char)*7
#define MAX_WORD_SIZE sizeof(char)*256
#define MAX_MEANING_SIZE sizeof(char)*65536

int main(int argc, char **argv)
{
    CLIENT *clnt;
    int *result;
    char *server;

    if (argc == 1) {
        printf("Missing RPC server\n");
        printf("e.g: ./rdict localhost\n");
        return 1;
    }

    /*
     * first argument is the RPC server to connect to
     */
    server = argv[1];

    clnt = clnt_create(server, DICTPROG, DICTVERS, "tcp"); 
    if (clnt == (CLIENT *)NULL) {
        clnt_pcreateerror(server);
        return 1;
    }

    /*
     * initialize variables for reading procedure, word, meaning
     * and values to compare procedure name against
     */
    char *proc = malloc(MAX_PROC_SIZE);
    char *word = malloc(MAX_WORD_SIZE);
    char *meaning = malloc(MAX_MEANING_SIZE);
    char *insert = "INSERT";
    char *lookup = "LOOKUP";
    if (proc == NULL || word == NULL || meaning == NULL) {
        printf("Error allocating memory\n");
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
        fgets(proc, MAX_PROC_SIZE, stdin);

        if (!strcmp(proc, insert)) {
            // call INSERT procedure
            printf("Enter word: ");
            // skip newline of previous input
            scanf("\n");
            fgets(word, MAX_WORD_SIZE, stdin);
            // remove trailing newline
            strtok(word, "\n");

            printf("Enter meaning: ");
            scanf("\n");
            fgets(meaning, MAX_MEANING_SIZE, stdin);
            strtok(meaning, "\n");

            result = insert_1(word, meaning, clnt);
            if (result == (int *)NULL) {
                clnt_perror(clnt, server);
                free(proc);
                free(word);
                free(meaning);
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
            scanf("\n");
            fgets(word, MAX_WORD_SIZE, stdin);
            strtok(word, "\n");

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
    free(proc);
    free(word);
    free(meaning);
    clnt_destroy( clnt );
    return 0;
}
