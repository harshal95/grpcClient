// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: kv.proto
#ifndef GRPC_kv_2eproto__INCLUDED
#define GRPC_kv_2eproto__INCLUDED

#include "kv.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc_impl {
class CompletionQueue;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc_impl

namespace grpc {
namespace experimental {
template <typename RequestT, typename ResponseT>
class MessageAllocator;
}  // namespace experimental
}  // namespace grpc

class kv final {
 public:
  static constexpr char const* service_full_name() {
    return "kv";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status get(::grpc::ClientContext* context, const ::GetRequest& request, ::GetResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>> Asyncget(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>>(AsyncgetRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>> PrepareAsyncget(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>>(PrepareAsyncgetRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void get(::grpc::ClientContext* context, const ::GetRequest* request, ::GetResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void get(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void get(::grpc::ClientContext* context, const ::GetRequest* request, ::GetResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      virtual void get(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>* AsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GetResponse>* PrepareAsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status get(::grpc::ClientContext* context, const ::GetRequest& request, ::GetResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GetResponse>> Asyncget(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GetResponse>>(AsyncgetRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GetResponse>> PrepareAsyncget(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GetResponse>>(PrepareAsyncgetRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void get(::grpc::ClientContext* context, const ::GetRequest* request, ::GetResponse* response, std::function<void(::grpc::Status)>) override;
      void get(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetResponse* response, std::function<void(::grpc::Status)>) override;
      void get(::grpc::ClientContext* context, const ::GetRequest* request, ::GetResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      void get(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::GetResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::GetResponse>* AsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::GetResponse>* PrepareAsyncgetRaw(::grpc::ClientContext* context, const ::GetRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_get_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_get() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestget(::grpc::ServerContext* context, ::GetRequest* request, ::grpc::ServerAsyncResponseWriter< ::GetResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_get<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_get() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::GetRequest, ::GetResponse>(
          [this](::grpc::ServerContext* context,
                 const ::GetRequest* request,
                 ::GetResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->get(context, request, response, controller);
                 }));
    }
    void SetMessageAllocatorFor_get(
        ::grpc::experimental::MessageAllocator< ::GetRequest, ::GetResponse>* allocator) {
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::GetRequest, ::GetResponse>*>(
          ::grpc::Service::experimental().GetHandler(0))
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_get<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_get() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_get() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestget(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_get() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->get(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void get(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_get() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::GetRequest, ::GetResponse>(std::bind(&WithStreamedUnaryMethod_get<BaseClass>::Streamedget, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status get(::grpc::ServerContext* context, const ::GetRequest* request, ::GetResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedget(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::GetRequest,::GetResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_get<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_get<Service > StreamedService;
};


#endif  // GRPC_kv_2eproto__INCLUDED