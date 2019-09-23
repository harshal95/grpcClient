#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../library/kv_client.h"

int main() {
	printf("Starting application in client in C!!\n");
	// char key[100] = "watch";
	// char value[100] = "Avengers";
	// char old_value[100];
	// int response_code = kv739_put(key, value, old_value);
	// // int response_code = kv739_get(key, value);
	// printf("Response code for put for key: %s in test_suite: %d\n", key, response_code);

	// response_code = kv739_get(key, value);
	// printf("Response code for get for key: %s in test_suite: %d\n", key, response_code);
	char** server_list = (char**)malloc(3 * sizeof(char*));
	for(int i = 0; i < 3; i++) {
		server_list[i] = (char*) malloc(50 * sizeof(char));
	}

	strcpy(server_list[0], "localhost:9090");
	strcpy(server_list[1], "localhost:9091");
	strcpy(server_list[2], "localhost:9092");

	int ret_val = kv739_init(server_list);

	printf("Return val from server creation: %d\n", ret_val);

	char newkey[100] = "tic";
	char newvalue[100] = "tac";
	char oldvalue[100];
	int put_response_code = kv739_put(newkey, newvalue, oldvalue);
	printf("Response code for put for key: %s in test_suite: %d\n", newkey, put_response_code);

	int response_code = kv739_get(newkey, newvalue);
	printf("Response code for get for key: %s in test_suite: %d\n", newkey, response_code);
	
	int shutdown_response = kv739_shutdown();
	printf("Shutdown response: %d\n", shutdown_response);

	int reinit_ret_val = kv739_init(server_list);
	printf("Reinit return val from server creation: %d\n", reinit_ret_val);

	int reinit_get_response_code = kv739_get(newkey, newvalue);
	printf("Reinit get response code for get for key: %s in test_suite: %d\n", newkey, reinit_get_response_code);


	// char putvalue[100] = "ball";
	// response_code = kv739_put(newkey, putvalue, oldvalue);
	// printf("Response code for put for key: %s in test_suite: %d\n", newkey, response_code);

	// response_code = kv739_get(newkey, oldvalue);
	// printf("Response code for get for key: %s in test_suite: %d\n", newkey, response_code);	


	return 0;
}
