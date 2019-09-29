#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../library/kv_client.h"

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**)malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main(int argc, char* argv[])
{
    FILE* fp;
    if(argc != 2) {
        printf("Give file path as input\n");
        return 0;
    }
    fp = fopen("test_file.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        printf("Line read: %s", line);
        if (line[read - 1] == '\n') {
              line[read - 1] = '\0';
              read--;
        }
        char** tokens;

        tokens = str_split(line, ',');
        int token_ct = 0;
        for(int i = 0; *(tokens + i); i++) {
            token_ct++;
        }
        if (tokens)
        {
            int i;
            if(strcmp(tokens[0], "init") == 0) {
                printf("Init operation invoked: \n");
                char** server_list = (char**)malloc((token_ct - 1) * sizeof(char*));
                for (i = 1; *(tokens + i); i++) {
                    server_list[i-1] = (char*)malloc(100 * sizeof(char));
                    strcpy(server_list[i-1], *(tokens + i));
                    printf("Adding server: %s\n", server_list[i-1]);
                }
                int response_code = kv739_init(server_list);
                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
            } else if(strcmp(tokens[0], "get") == 0) {
                printf("Get operation invoked: \n");
                
                char* key = *(tokens + 1);
                char value[100];
                value[0] = '\0';

                int response_code = kv739_get(key, value);
                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
            } else if(strcmp(tokens[0], "put") == 0) {
                printf("Put operation invoked: \n");

                char* newkey = *(tokens + 1); 
                char* newvalue = *(tokens + 2);
                char oldvalue[100];
                oldvalue[0] = '\0';

                int response_code = kv739_put(newkey, newvalue, oldvalue);
                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
            } else if(strcmp(tokens[0], "shutdown") == 0) {
                printf("Shutdown operation invoked: \n");
                int response_code = kv739_shutdown();
            }
        }
    }

    fclose(fp);
    //char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    

    return 0;
}
