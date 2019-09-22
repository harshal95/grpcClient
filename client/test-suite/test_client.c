#include <stdio.h>
#include "../library/kv_client.h"

int main() {
	printf("Starting application in client in C!!");
	char key[100] = "drink";
	char value[100];

	int response_code = kv739_get(key, value);
	printf("Response code for get for key: %s in test_suite: %d\n", key, response_code);
	return 0;
}
