/*
*	GrpcImpl.h
*
*
*/
#ifndef GRPC_IMPL_H
#define GRPC_IMPL_H


#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "route_guide.grpc.pb.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "interactive_icp.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using namespace routeguide;

using std::chrono::system_clock;


class RouteGuideImpl final : public RouteGuide::Service {
public:
	explicit RouteGuideImpl() {

	}

	Status CheckServer(ServerContext* context, const ServerInfoRequest* request, ServerInfoReply* reply) override ;

	Status SetIcpTemplet(ServerContext* context, ServerReader<TempletFileRequest>* reader,TempletFileReply* reply) override ;

	Status RouteChat(ServerContext* context, ServerReaderWriter<RouteNote, RouteNote>* stream) override ;

	
	Status SetIcpMaxIterations(ServerContext* context, const IcpMaxIterationsRequest* request, IcpMaxIterationsReply* reply) override ;

private:
	ApiPCL objPcl;
	//std::vector<Feature> feature_list_;
};

#endif