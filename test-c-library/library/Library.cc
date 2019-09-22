#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#ifdef BAZEL_BUILD
#include "protos/kv.grpc.pb.h"
#else
#include "kv.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class ClientServerInterface {
    private:
        std::unique_ptr<kv::Stub> stub_;

    public:
        ClientServerInterface(std::shared_ptr<Channel> channel);
        std::string get_request(const std::string&);
};

ClientServerInterface::ClientServerInterface (
        std::shared_ptr<Channel> channel
        )
    : stub_(kv::NewStub(channel)) {
}

std::string ClientServerInterface::get_request(const std::string& key) {

    /* Create Get Request */
    GetRequest request;
    request.set_key(key);
    /* Create Response */
    GetResponse response;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    Status status = stub_->get(&context, request, &response);
    if (status.ok()) {
        return "success";
    } else {
        std::cout << " L: " << status.error_code() << " : " << status.error_message()
            << std::endl;
        return "failure";
    }
}

int kv739_get(char * key, char * value) {

    /* Create Strings Key/Values */
    std::string key_request(key);

    ClientServerInterface c(
        grpc::CreateChannel(
                "localhost:7070",
                grpc::InsecureChannelCredentials()));
    /* Send request to server */
    std::string response_code = c.get_request(key_request);

    return 0;
}
