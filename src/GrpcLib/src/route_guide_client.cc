/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
//#include "stdio.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "route_guide.grpc.pb.h"


#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using namespace routeguide;


typedef unsigned char BYTE;
#define CHUCK_SIZE 4096
static int pkgIndex = 1;


class RouteGuideClient
{
public:
  RouteGuideClient(std::shared_ptr<Channel> channel)
    : stub_(RouteGuide::NewStub(channel))
  {
  }


  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  ServerInfoReply CheckServer(const std::string& message) {
    // Data we are sending to the server.
    ServerInfoRequest request;
    request.set_message(message);

    // Container for the data we expect from the server.
    ServerInfoReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->CheckServer(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return reply;
    }
  }
  private:
  std::unique_ptr<RouteGuide::Stub> stub_;

};

int main(int argc, char** argv) {
  // Expect only arg: --db_path=path/to/route_guide_db.json.
  //std::string db = routeguide::GetDbFileContent(argc, argv);
  RouteGuideClient guide(
    grpc::CreateChannel("localhost:50051",
                        grpc::InsecureChannelCredentials()));

  std::cout << "-------------- GetFeature --------------" << std::endl;

  ServerInfoReply reply = guide.CheckServer("");
  std::cout << "Greeter received revsion:: " << reply.revsion() << std::endl;
  std::cout << "Greeter received revsion:: " << reply.builddate() << std::endl;
  std::cout << "Greeter received revsion:: " << reply.complayname() << std::endl;

  return 0;
}
