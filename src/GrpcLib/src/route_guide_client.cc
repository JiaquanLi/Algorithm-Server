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
using routeguide::Point;
using routeguide::Feature;
using routeguide::Rectangle;
using routeguide::RouteSummary;
using routeguide::RouteNote;
using routeguide::RouteGuide;


typedef unsigned char BYTE;
#define CHUCK_SIZE 4096

static int pkgIndex = 1;
namespace routeguide {

std::string GetDbFileContent(int argc, char** argv) {
  std::string db_path;
  std::string arg_str("--db_path");
  if (argc > 1) {
    std::string argv_1 = argv[1];
    size_t start_position = argv_1.find(arg_str);
    if (start_position != std::string::npos) {
      start_position += arg_str.size();
      if (argv_1[start_position] == ' ' ||
          argv_1[start_position] == '=') {
        db_path = argv_1.substr(start_position + 1);
      }
    }
  } else {
    db_path = "route_guide_db.json";
  }
  std::ifstream db_file(db_path);
  if (!db_file.is_open()) {
    std::cout << "Failed to open " << db_path << std::endl;
    return "";
  }
  std::stringstream db;
  db << db_file.rdbuf();
  return db.str();
}

// A simple parser for the json db file. It requires the db file to have the
// exact form of [{"location": { "latitude": 123, "longitude": 456}, "name":
// "the name can be empty" }, { ... } ... The spaces will be stripped.
class Parser {
 public:
  explicit Parser(const std::string& db) : db_(db) {
    // Remove all spaces.
    db_.erase(
        std::remove_if(db_.begin(), db_.end(), isspace),
        db_.end());
    if (!Match("[")) {
      SetFailedAndReturnFalse();
    }
  }

  bool Finished() {
    return current_ >= db_.size();
  }

  bool TryParseOne(Feature* feature) {
    if (failed_ || Finished() || !Match("{")) {
      return SetFailedAndReturnFalse();
    }
    if (!Match(location_) || !Match("{") || !Match(latitude_)) {
      return SetFailedAndReturnFalse();
    }
    long temp = 0;
    ReadLong(&temp);
    feature->mutable_location()->set_latitude(temp);
    if (!Match(",") || !Match(longitude_)) {
      return SetFailedAndReturnFalse();
    }
    ReadLong(&temp);
    feature->mutable_location()->set_longitude(temp);
    if (!Match("},") || !Match(name_) || !Match("\"")) {
      return SetFailedAndReturnFalse();
    }
    size_t name_start = current_;
    while (current_ != db_.size() && db_[current_++] != '"') {
    }
    if (current_ == db_.size()) {
      return SetFailedAndReturnFalse();
    }
    feature->set_name(db_.substr(name_start, current_-name_start-1));
    if (!Match("},")) {
      if (db_[current_ - 1] == ']' && current_ == db_.size()) {
        return true;
      }
      return SetFailedAndReturnFalse();
    }
    return true;
  }

 private:

  bool SetFailedAndReturnFalse() {
    failed_ = true;
    return false;
  }

  bool Match(const std::string& prefix) {
    bool eq = db_.substr(current_, prefix.size()) == prefix;
    current_ += prefix.size();
    return eq;
  }

  void ReadLong(long* l) {
    size_t start = current_;
    while (current_ != db_.size() && db_[current_] != ',' && db_[current_] != '}') {
      current_++;
    }
    // It will throw an exception if fails.
    *l = std::stol(db_.substr(start, current_ - start));
  }

  bool failed_ = false;
  std::string db_;
  size_t current_ = 0;
  const std::string location_ = "\"location\":";
  const std::string latitude_ = "\"latitude\":";
  const std::string longitude_ = "\"longitude\":";
  const std::string name_ = "\"name\":";
};

void ParseDb(const std::string& db, std::vector<Feature>* feature_list) {
  feature_list->clear();
  std::string db_content(db);
  db_content.erase(
      std::remove_if(db_content.begin(), db_content.end(), isspace),
      db_content.end());

  Parser parser(db_content);
  Feature feature;
  while (!parser.Finished()) {
    feature_list->push_back(Feature());
    if (!parser.TryParseOne(&feature_list->back())) {
      std::cout << "Error parsing the db file";
      feature_list->clear();
      break;
    }
  }
  std::cout << "DB parsed, loaded " << feature_list->size()
            << " features." << std::endl;
}


}  // namespace routeguide

class RouteGuideClient {
 public:
  RouteGuideClient(std::shared_ptr<Channel> channel)
      : stub_(RouteGuide::NewStub(channel)) {
    //routeguide::ParseDb(db, &feature_list_);
  }


    void RouteChat() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<RouteNote, RouteNote> > stream(
        stub_->RouteChat(&context));

    std::thread writer([stream]() {
  
      time_t tBeginTime = time(NULL);
      clock_t start, end;
      start = clock();

        long l_GetSize = 0;

        FILE* file;
    	file = fopen("test.txt", "rb+");
	fseek(file, 0, SEEK_SET);
    	long length = -1;
	std::cout <<"new buffer"<< std::endl;
	char buffer [1024*pkgIndex + 1];
	std::cout <<"new buffer ok"<< std::endl;
        if (file == NULL) return;

        long l_TotalSize = fseek(file, 0, SEEK_END);
        l_TotalSize = ftell(file);
        fseek(file, 0, SEEK_SET);
	memset(buffer, '\0', sizeof(buffer));
	while( /*getline(fs,strline)*/ length = fread(buffer, 1, 1024*pkgIndex, file) >0 ){
    		
		//std::cout << "size:" << strline.length()<<std::endl;
		//std::cout << "cotent:" << strline<<std::endl;
    		//fread(buffer, 1, length, file);
    		
		RouteNote noteSend;
		noteSend.set_datasend(buffer);
		noteSend.set_size(strlen(buffer));
	  	stream->Write(noteSend);
	std::cout << "send:" << buffer<<std::endl;
		memset(buffer, '\0', sizeof(buffer));
		}

        fclose(file);

        stream->WritesDone();
        
    });

    FILE* file2;
    file2 = fopen("test2.txt", "wb+");
    RouteNote server_note;
    while (stream->Read(&server_note)) {
      //fwrite((void*)server_note.datasend().c_str(), server_note.size(), 1, file2);
	std::cout << "Get from server:" << server_note.datasend().c_str()<<std::endl;
    }
    
    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "RouteChat rpc failed." << std::endl;
    }
  }

 private:

  bool GetOneFeature(const Point& point, Feature* feature) {
    ClientContext context;
    Status status = stub_->GetFeature(&context, point, feature);
    if (!status.ok()) {
      std::cout << "GetFeature rpc failed." << std::endl;
      return false;
    }
    if (!feature->has_location()) {
      std::cout << "Server returns incomplete feature." << std::endl;
      return false;
    }
    if (feature->name().empty()) {
      std::cout << "Found no feature at "
                << feature->location().latitude()/kCoordFactor_ << ", "
                << feature->location().longitude()/kCoordFactor_ << std::endl;
    } else {
      std::cout << "Found feature called " << feature->name()  << " at "
                << feature->location().latitude()/kCoordFactor_ << ", "
                << feature->location().longitude()/kCoordFactor_ << std::endl;
    }
    return true;
  }

  const float kCoordFactor_ = 10000000.0;
  std::unique_ptr<RouteGuide::Stub> stub_;
  std::vector<Feature> feature_list_;
};

int main(int argc, char** argv) {
  // Expect only arg: --db_path=path/to/route_guide_db.json.
  //std::string db = routeguide::GetDbFileContent(argc, argv);
  RouteGuideClient guide(
      grpc::CreateChannel("localhost:50051",
                          grpc::InsecureChannelCredentials()));

    std::cout << "-------------- GetFeature --------------" << std::endl;
  guide.RouteChat();

  return 0;
}
