// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: kvStore.proto

#include "kvStore.pb.h"
#include "kvStore.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char* kvStore_method_names[] = {
  "/kvStore/get",
  "/kvStore/put",
};

std::unique_ptr< kvStore::Stub> kvStore::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< kvStore::Stub> stub(new kvStore::Stub(channel));
  return stub;
}

kvStore::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_get_(kvStore_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_put_(kvStore_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status kvStore::Stub::get(::grpc::ClientContext* context, const ::GetRequest& request, ::GetResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_get_, context, request, response);
}

void kvStore::Stub::experimental_async::get(::grpc::ClientContext* context, const ::GetRequest* request, ::GetResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_get_, context, request, response, std::move(f));
}

void kvStore::Stub::experimental_async::get(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_get_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::GetResponse>* kvStore::Stub::AsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GetResponse>::Create(channel_.get(), cq, rpcmethod_get_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::GetResponse>* kvStore::Stub::PrepareAsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::GetResponse>::Create(channel_.get(), cq, rpcmethod_get_, context, request, false);
}

::grpc::Status kvStore::Stub::put(::grpc::ClientContext* context, const ::PutRequest& request, ::PutResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_put_, context, request, response);
}

void kvStore::Stub::experimental_async::put(::grpc::ClientContext* context, const ::PutRequest* request, ::PutResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_put_, context, request, response, std::move(f));
}

void kvStore::Stub::experimental_async::put(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::PutResponse* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_put_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::PutResponse>* kvStore::Stub::AsyncputRaw(::grpc::ClientContext* context, const ::PutRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::PutResponse>::Create(channel_.get(), cq, rpcmethod_put_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::PutResponse>* kvStore::Stub::PrepareAsyncputRaw(::grpc::ClientContext* context, const ::PutRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::PutResponse>::Create(channel_.get(), cq, rpcmethod_put_, context, request, false);
}

kvStore::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      kvStore_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< kvStore::Service, ::GetRequest, ::GetResponse>(
          std::mem_fn(&kvStore::Service::get), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      kvStore_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< kvStore::Service, ::PutRequest, ::PutResponse>(
          std::mem_fn(&kvStore::Service::put), this)));
}

kvStore::Service::~Service() {
}

::grpc::Status kvStore::Service::get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status kvStore::Service::put(::grpc::ServerContext* context, const ::PutRequest* request, ::PutResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

