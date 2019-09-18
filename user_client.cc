#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#ifdef BAZEL_BUILD
#include "protos/user.grpc.pb.h"
#else
#include "user.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
//using sampleClient::LoginRequest;
//using sampleClient::Empty;
//using sampleClient::APIResponse;
//using sampleClient::user;

class LoginClient {
 public:
  LoginClient(std::shared_ptr<Channel> channel)
      : stub_(user::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user, const std::string& password) {
    // Data we are sending to the server.
    LoginRequest request;
    request.set_username(user);
    request.set_password(password);
    // Container for the data we expect from the server.
    APIResponse reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->login(&context, request, &reply);
    // Act upon its status.
    if (status.ok()) {
      return reply.responsemessage();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<user::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 9090). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  std::cout << "Inside main" << std::endl;
  LoginClient loginClient(grpc::CreateChannel(
      "localhost:9090", grpc::InsecureChannelCredentials()));
  std::string user("harshal");
  std::string password("harshal");
  std::string reply = loginClient.SayHello(user, password);
  std::cout << "Response received: " << reply << std::endl;

  return 0;
}

