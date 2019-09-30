#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
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
    FILE* ofp;
    if(argc != 3) {
        printf("Give file path for input and output\n");
        return 0;
    }
    fp = fopen(argv[1], "r");
    ofp = fopen(argv[2], "w");

    if (fp == NULL || ofp == NULL)
        exit(EXIT_FAILURE);
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    double n = 0;
    double overall_latency = 0;

    clock_t t; 
    t = clock();

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
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
            n++;
            int i;
            if(strcmp(tokens[0], "init") == 0) {
                printf("Init operation invoked: \n");
                //clock_t t; 
                //t = clock(); 

                int base_port = atoi(tokens[1]);

                int server_count = atoi(tokens[2]);
                char** server_list = (char**)malloc((server_count) * sizeof(char*));
                for (i = 0; i < server_count; i++) {
                    server_list[i] = (char*)malloc(100 * sizeof(char));
                    char port[10];
                    //itoa(base_port + i, port, 10);
                    snprintf(port, sizeof(port), "%d", base_port + i);
                    strcpy(server_list[i], "localhost:");
                    strcat(server_list[i], port);
                    printf("Adding server: %s\n", server_list[i]);
                }
                int response_code = -1;
                response_code = kv739_init(server_list);
                //t = clock() - t; 
                //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
                
                fprintf(ofp, "%d",response_code);
                // fprintf(ofp, "%f\n",time_taken);
                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
                //printf("Init operation took: %f\n", time_taken);
                //overall_latency += time_taken;

            } else if(strcmp(tokens[0], "get") == 0) {
                printf("Get operation invoked: \n");
                //clock_t t; 
                //t = clock(); 
                char* key = *(tokens + 1);
                char value[100];
                value[0] = '\0';

                int response_code = -1;
                response_code = kv739_get(key, value);

                //t = clock() - t; 
                //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
                fprintf(ofp, "%d,", response_code);
                fprintf(ofp, "%s,", key);
                fprintf(ofp, "%s", value);
                //fprintf(ofp, "%f\n", time_taken);

                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
                //printf("Get operation took: %f\n", time_taken);
                //overall_latency += time_taken;
            } else if(strcmp(tokens[0], "put") == 0) {
                printf("Put operation invoked: \n");
                //clock_t t; 
                //t = clock(); 

                char* newkey = *(tokens + 1); 
                char* newvalue = *(tokens + 2);
                char oldvalue[100];
                oldvalue[0] = '\0';
                int response_code = -1;
                response_code = kv739_put(newkey, newvalue, oldvalue);
                //t = clock() - t; 
                //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

                fprintf(ofp, "%d,", response_code);
                fprintf(ofp, "%s,", newkey);
                fprintf(ofp, "%s,", newvalue);
                fprintf(ofp, "%s", oldvalue);
                //fprintf(ofp, "%f\n", time_taken);

                for (i = 0; *(tokens + i); i++) {
                    free(*(tokens + i));
                }
                free(tokens);
                //printf("Put operation took: %f\n", time_taken);
                //overall_latency += time_taken;
            } else if(strcmp(tokens[0], "shutdown") == 0) {
                printf("Shutdown operation invoked: \n");
                //clock_t t; 
                //t = clock(); 
                int response_code = -1;
                response_code = kv739_shutdown();
                //t = clock() - t; 
                //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
                fprintf(ofp, "%d", response_code);
                //fprintf(ofp, "%f\n", time_taken);
                //printf("Shutdown operation took: %f\n", time_taken);
                //overall_latency += time_taken;
            }
        }
    }

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    printf("overall_latency: %f\n", time_taken);
    printf("throughput: %f\n", n /time_taken);
    fclose(fp);
    fclose(ofp);
    //char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    

    return 0;
}

