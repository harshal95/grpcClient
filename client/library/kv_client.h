#ifndef KV_STORE_CLIENT_H_
#define KV_STORE_CLIENT_H_

int kv739_get(char* key, char* value);
int kv739_put(char* key, char* value, char* old_value);
int kv739_init(char** server_list);

#endif
