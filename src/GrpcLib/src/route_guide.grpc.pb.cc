// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: route_guide.proto

#include "route_guide.pb.h"
#include "route_guide.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace routeguide {

static const char* RouteGuide_method_names[] = {
  "/routeguide.RouteGuide/RouteChat",
  "/routeguide.RouteGuide/CheckServer",
  "/routeguide.RouteGuide/CheckLisence",
};

std::unique_ptr< RouteGuide::Stub> RouteGuide::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< RouteGuide::Stub> stub(new RouteGuide::Stub(channel));
  return stub;
}

RouteGuide::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_RouteChat_(RouteGuide_method_names[0], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_CheckServer_(RouteGuide_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CheckLisence_(RouteGuide_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::ClientReaderWriter< ::routeguide::RouteNote, ::routeguide::RouteNote>* RouteGuide::Stub::RouteChatRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::routeguide::RouteNote, ::routeguide::RouteNote>::Create(channel_.get(), rpcmethod_RouteChat_, context);
}

::grpc::ClientAsyncReaderWriter< ::routeguide::RouteNote, ::routeguide::RouteNote>* RouteGuide::Stub::AsyncRouteChatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::routeguide::RouteNote, ::routeguide::RouteNote>::Create(channel_.get(), cq, rpcmethod_RouteChat_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::routeguide::RouteNote, ::routeguide::RouteNote>* RouteGuide::Stub::PrepareAsyncRouteChatRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::routeguide::RouteNote, ::routeguide::RouteNote>::Create(channel_.get(), cq, rpcmethod_RouteChat_, context, false, nullptr);
}

::grpc::Status RouteGuide::Stub::CheckServer(::grpc::ClientContext* context, const ::routeguide::ServerInfoRequest& request, ::routeguide::ServerInfoReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CheckServer_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::routeguide::ServerInfoReply>* RouteGuide::Stub::AsyncCheckServerRaw(::grpc::ClientContext* context, const ::routeguide::ServerInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::routeguide::ServerInfoReply>::Create(channel_.get(), cq, rpcmethod_CheckServer_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::routeguide::ServerInfoReply>* RouteGuide::Stub::PrepareAsyncCheckServerRaw(::grpc::ClientContext* context, const ::routeguide::ServerInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::routeguide::ServerInfoReply>::Create(channel_.get(), cq, rpcmethod_CheckServer_, context, request, false);
}

::grpc::Status RouteGuide::Stub::CheckLisence(::grpc::ClientContext* context, const ::routeguide::LisenceInfoRequest& request, ::routeguide::LisenceInfoReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CheckLisence_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::routeguide::LisenceInfoReply>* RouteGuide::Stub::AsyncCheckLisenceRaw(::grpc::ClientContext* context, const ::routeguide::LisenceInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::routeguide::LisenceInfoReply>::Create(channel_.get(), cq, rpcmethod_CheckLisence_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::routeguide::LisenceInfoReply>* RouteGuide::Stub::PrepareAsyncCheckLisenceRaw(::grpc::ClientContext* context, const ::routeguide::LisenceInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::routeguide::LisenceInfoReply>::Create(channel_.get(), cq, rpcmethod_CheckLisence_, context, request, false);
}

RouteGuide::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RouteGuide_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< RouteGuide::Service, ::routeguide::RouteNote, ::routeguide::RouteNote>(
          std::mem_fn(&RouteGuide::Service::RouteChat), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RouteGuide_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RouteGuide::Service, ::routeguide::ServerInfoRequest, ::routeguide::ServerInfoReply>(
          std::mem_fn(&RouteGuide::Service::CheckServer), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RouteGuide_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RouteGuide::Service, ::routeguide::LisenceInfoRequest, ::routeguide::LisenceInfoReply>(
          std::mem_fn(&RouteGuide::Service::CheckLisence), this)));
}

RouteGuide::Service::~Service() {
}

::grpc::Status RouteGuide::Service::RouteChat(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::routeguide::RouteNote, ::routeguide::RouteNote>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status RouteGuide::Service::CheckServer(::grpc::ServerContext* context, const ::routeguide::ServerInfoRequest* request, ::routeguide::ServerInfoReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status RouteGuide::Service::CheckLisence(::grpc::ServerContext* context, const ::routeguide::LisenceInfoRequest* request, ::routeguide::LisenceInfoReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace routeguide

