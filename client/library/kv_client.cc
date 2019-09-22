#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#ifdef BAZEL_BUILD
#include "protos/kvStore.grpc.pb.h"
#else
#include "kvStore.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class KVStoreClient {
 public:
  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int get(const std::string& key, const std::string& value) {
    // Data we are sending to the server.
    GetRequest get_request;
    get_request.set_requestkey(key);
    get_request.set_requestvalue(value);
    // Container for the data we expect from the server.
    GetResponse get_response;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->get(&context, get_request, &get_response);
    // Act upon its status.
    if (status.ok()) {
      std::cout << "Get response value: " << get_response.responsevalue() << std::endl;
      return get_response.status();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -1;
      //return "RPC failed";
    }
  }

  int put(const std::string& key, const std::string& value, const std::string& oldvalue) {
    PutRequest put_request;
    put_request.set_requestkey(key);
    put_request.set_requestnewvalue(value);
    put_request.set_requestoldvalue(oldvalue);

    PutResponse put_response;

    ClientContext context;

    Status status = stub_->put(&context, put_request, &put_response);

    if(status.ok()) {
      std::cout << "put value : " << put_response.responsenewvalue() << std::endl;
      return put_response.status();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
      return -1;
        //return "RPC failed";
    }
}

static KVStoreClient* Instance() {
  if(!client_instance) {
    client_instance = new KVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));
  }
  return client_instance;
}

 private:
  std::unique_ptr<kvStore::Stub> stub_;
  KVStoreClient(std::shared_ptr<Channel> channel)
      : stub_(kvStore::NewStub(channel)) {}
  static KVStoreClient* client_instance;

};

KVStoreClient* KVStoreClient::client_instance = NULL;

int kv739_get(char* key, char* value) {
  std::string key_string(key);
  std::string value_string(value);
  //KVStoreClient kVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));
  int response_code = KVStoreClient::Instance() -> get(key_string, value_string);
  std::cout << "Response code from Get for key: " << response_code << std::endl;
  std::cout << "Printing response from Get for key: " << key_string << " and value: " << value_string << std::endl;
  return response_code;
}

int kv739_put(char* key, char* value, char* old_value) {
  std::string key_string(key);
  std::string value_string(value);
  std::string old_value_string(old_value);
  //KVStoreClient kVStoreClient(grpc::CreateChannel("localhost:9090", grpc::InsecureChannelCredentials()));
  int response_code = KVStoreClient::Instance() -> put(key_string, value_string, old_value_string);
  std::cout << "Response code from Put for key: " << response_code << std::endl;
  std::cout << "Printing response from Put for key: " << key_string << " and value: " << value_string << " and old_value: " << old_value_string << std::endl;  
  return response_code; 
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
