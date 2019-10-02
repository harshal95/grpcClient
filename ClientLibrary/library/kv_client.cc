#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <exception>
#include <chrono>
#ifdef BAZEL_BUILD
#include "protos/kvStore.grpc.pb.h"
#else
#include "kvStore.grpc.pb.h"
#endif

//#define MAX_VALUE 100

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
int n;

class KVStoreClient {
 public:

  
  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int get(std::string& key, std::string& value) {
    // Data we are sending to the server.
    GetRequest get_request;
    get_request.set_requestkey(key);
    get_request.set_requestvalue(value);
    // Container for the data we expect from the server.
    GetResponse get_response;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    unsigned int client_connection_timeout = 100000;


    std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + 
    std::chrono::milliseconds(client_connection_timeout);

    // context.set_wait_for_ready(true);
    context.set_deadline(deadline);

    bool success = false;
    // The actual RPC.
    Status status = stub_->get(&context, get_request, &get_response);
    
    // Act upon its status.
    if(status.ok()) {
      std::cout << "Get response value: " << get_response.responsevalue() << std::endl;
      value = get_response.responsevalue();
      return get_response.status();
    } else {

      std::cout << status.error_code() << ": " << status.error_message() << " in get operation"
                << std::endl;
      //return "RPC failed";
    }
    
    return -1;
  }

  int put(std::string& key, std::string& value, std::string& oldvalue) {
    PutRequest put_request;
    put_request.set_requestkey(key);
    put_request.set_requestnewvalue(value);
    put_request.set_requestoldvalue(oldvalue);
    put_request.set_updatenode(-1);

    PutResponse put_response;


    ClientContext context;
    unsigned int client_connection_timeout = 100000;

    std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + 
    std::chrono::milliseconds(client_connection_timeout);
    // context.set_wait_for_ready(true);
    context.set_deadline(deadline);

  
    Status status = stub_->put(&context, put_request, &put_response);
    

    if(status.ok()) {
      std::cout << "put value : " << put_response.responsenewvalue() << std::endl;
      oldvalue = put_response.responseoldvalue();
      value = put_response.responsenewvalue();
      return put_response.status();
    } else {
      std::cout << status.error_code() << ": " << status.error_message() <<" in put operation"
                  << std::endl;
    }
    
    return -1;
}
// static KVStoreClient** CreatedInstance() {
//   return client_instance;
// }

static KVStoreClient** Instance(char** server_list) {
  if(server_list == NULL)
    return client_instance;
  std::ifstream in("server_instances.txt");
  std::string str;

  if(std::getline(in, str)) {
    n = std::stoi(str);
  }
  // int n = sizeof(server_list)/sizeof(server_list[0]);
  std::cout<<"n : "<<n<<std::endl;
  client_instance = (KVStoreClient**)malloc(n * sizeof(KVStoreClient*));
  // for(int i = 0; i < sizeof(server_list)/sizeof(server_list[0]); i++) {
  for(int i = 0; i < n; i++) {
    //client_instance[i] = (KVStoreClient* )malloc(sizeof(KVStoreClient));
    client_instance[i] = new KVStoreClient(grpc::CreateChannel(server_list[i], grpc::InsecureChannelCredentials()));
  }
  //client_instance = new KVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));

  return client_instance;
}

 private:
  std::unique_ptr<kvStore::Stub> stub_;
  
  static KVStoreClient** client_instance;
  KVStoreClient(std::shared_ptr<Channel> channel)
      : stub_(kvStore::NewStub(channel)) {}

};

KVStoreClient** KVStoreClient::client_instance = NULL;

int kv739_get(char* key, char* value) {
  std::cout<<"inside get"<<std::endl;
  std::string key_string(key);
  std::string value_string(value);
  //KVStoreClient kVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));
  KVStoreClient** connection_list = KVStoreClient::Instance(NULL);
  for(int i = 0; i < n; i++) {
    if(connection_list[i] == NULL) {
      std::cout<<"connection shut for " << i << std::endl;
    }
  }

 

  KVStoreClient* connect_obj = NULL;
  // for(int i = 0; i < sizeof(connection_list)/sizeof(connection_list[0]); i++) {
  // for(int i = 0; i < n; i++) {
  //   if(connect_obj == NULL) {
  //     connect_obj = connection_list[i];
  //   }
  // }
  int i = rand() % n;
  int response_code = -1;
  int deadcount = 0;
  int visited[n];
  for(int i = 0; i < n; i++) {
    visited[i] = 0;
  }
  while(deadcount < n && response_code == -1) {
    connect_obj = connection_list[i];
    // if(connect_obj == NULL) {
      std::cout<<"inside empty connect : " << i << std::endl;
        
    
  //connect_obj = connection_list[2];

    response_code = connect_obj -> get(key_string, value_string);
    if(response_code == -1) {
      if(visited[i] == 0) {
          visited[i] = 1;
          deadcount++;
          if(deadcount == n)
            break;
          i = rand() % n;
          continue;  
      } else {
          i = rand() % n;
          continue;  
      }
    } else {
      strcpy(value, value_string.c_str());
      std::cout << "Get succeeded at: " << i << std::endl;
      std::cout << "Response code from Get for key: " << response_code << std::endl;
      std::cout << "Printing response from Get for key: " << key_string << " and value: " << value_string << std::endl;
      return response_code;
    }
  }

  if(response_code == -1) {
    return response_code;
  }
  //int response_code = kVStoreClient.get(key_string, value_string);

  
  return response_code;
}

int kv739_put(char* key, char* value, char* old_value) {
  std::string key_string(key);
  std::string value_string(value);
  std::string old_value_string(old_value);
  //KVStoreClient kVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));

  KVStoreClient** connection_list = KVStoreClient::Instance(NULL);
  KVStoreClient* connect_obj = NULL;

  //TODO: Pick random server
  // connect_obj = connection_list[2];
  std::cout<<"connection list size: "<< sizeof(connection_list)<<std::endl;
  

  // for(int i = 0; i < n; i++) {
  //   if(connect_obj == NULL) {
  //     connect_obj = connection_list[i];
  //   }
  // }
  //connect_obj = connection_list[2];

  // if(connect_obj == NULL) {
  //   return -1;
  // }



  int i = rand() % n;
  int response_code = -1;
  int deadcount = 0;
  int visited[n];
  for(int i = 0; i < n; i++) {
    visited[i] = 0;
  }
  while(deadcount < n && response_code == -1) {
    connect_obj = connection_list[i];
    // if(connect_obj == NULL) {        
    
  //connect_obj = connection_list[2];

    response_code = connect_obj -> put(key_string, value_string, old_value_string);
    if(response_code == -1) {
      if(visited[i] == 0) {
          visited[i] = 1;
          deadcount++;
          if(deadcount == n)
            break;
          i = rand() % n;
          continue;  
      } else {
          i = rand() % n;
          continue;  
      }
    } else {
      strcpy(value, value_string.c_str());
      strcpy(old_value, old_value_string.c_str());
      std::cout << "Put succeeded at: " << i << std::endl;
      std::cout << "Response code from Put for key: " << response_code << std::endl;
      std::cout << "Printing response from Put for key: " << key_string << " and value: " << value_string << " and old_value: " << old_value_string << std::endl;  
      return response_code;     
    }
  }  
  return response_code;
  



  // int i = 0;
  // int response_code = -1;
  // while(i < n && response_code == -1) {
  //   connect_obj = connection_list[i];
  //   if(connect_obj == NULL) {
  //     i++;
  //     continue;
  //   }
  //   response_code = connect_obj -> put(key_string, value_string, old_value_string);
  //   strcpy(old_value, old_value_string.c_str());
  //   strcpy(value, value_string.c_str());
  //   i++;
  // }
  //int response_code = kVStoreClient.put(key_string, value_string, old_value_string);
  
}

int kv739_init(char** server_list) {
  KVStoreClient** connection_list = KVStoreClient::Instance(server_list);
  for(int i = 0; i < n; i++) {
    if(connection_list[i] != NULL) {
      return 0;
    }
  }
  return -1;
}

int kv739_shutdown(void) {
  KVStoreClient** connection_list = KVStoreClient::Instance(NULL);
  for(int i = 0; i < n; i++) {
    if(connection_list[i] != NULL) {
       std::cout << "shutting down connection : " << i << std::endl;
       //free(connection_list[i]);
       connection_list[i] = NULL;
    }
  }
  for(int i = 0; i < n; i++) {
    if(connection_list[i] != NULL) {
      std::cout << "shutdown failed for : " << i << std::endl;
    }
  }
  //free(connection_list);

  connection_list = NULL;

  return 0;
}


// int main(int argc, char** argv) {
//   // Instantiate the client. It requires a channel, out of which the actual RPCs
//   // are created. This channel models a connection to an endpoint (in this case,
//   // localhost at port 9090). We indicate that the channel isn't authenticated
//   // (use of InsecureChannelCredentials()).
//   std::cout << "Inside main" << std::endl;
//   KVStoreClient kVStoreClient(grpc::CreateChannel(
//       "localhost:9090", grpc::InsecureChannelCredentials()));
//   std::string key("hello");
//   std::string value("tea");
//   std::string oldvalue("");
//   int reply = kVStoreClient.get(key, value);
//   std::cout << "Response received: " << reply << std::endl;

//   reply = kVStoreClient.put(key, value, oldvalue);
//   std::cout << "Response received: " << reply << std::endl;

//   reply = kVStoreClient.get(key, value);
//   std::cout << "Response received: " << reply << std::endl;
//   return 0;
// }

