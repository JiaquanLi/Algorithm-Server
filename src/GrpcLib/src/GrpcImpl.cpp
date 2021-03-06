/*
*
*  GrpcImpl.h
*
*/

#include"GrpcImpl.h"

//#define RPC_PCL_DEBUG	0
#define TARGET_FILE   "target.txt"
#define TEMPLET_FILE  "templet.txt"

Status RouteGuideImpl:: CheckServer(ServerContext* context, const ServerInfoRequest* request, ServerInfoReply* reply) {

	std::cout << "read client licence:" << request->message().c_str() << std::endl;
	reply->set_revsion("1.00");
	reply->set_builddate("2018.09.28");
	reply->set_complayname("uAI");
	return Status::OK;
}

Status RouteGuideImpl::SetIcpTemplet(ServerContext* context, ServerReader<TempletFileRequest>* reader, TempletFileReply* reply) {

	bool b_ret = false;
	long fileSize = 0;
	char* templetFile = (char*)"templet.txt";

	FILE* fileSave;
	fileSave = fopen(templetFile, "wb+");

	TempletFileRequest note;
	while (reader->Read(&note)) {

		fwrite((void*)note.datasend().c_str(), note.size(), 1, fileSave);
		fileSize += note.size();
	}

	fclose(fileSave);
	std::cout << "Get Templet File " << "size:" << fileSize << std::endl;

	b_ret = objPcl.CreateLoadIcpPcdFile((char*)TEMPLET_FILE);

	reply->set_retsts(b_ret);
	return Status::OK;
}

Status RouteGuideImpl::RouteChat(ServerContext* context,
                                 ServerReaderWriter<RouteNote, RouteNote>* stream) {
	std::vector<RouteNote> received_notes;

	//char* targetFile = (char*)"target.txt";
	//char* templetFile = (char*)"templet.txt";
	RouteNote server_note;
	RouteNote note;

#ifdef RPC_PCL_DEBUG  //we will not update target file in debug model
	while (stream->Read(&note)) {
	
	}
	std::cout << "In debug model use local file: " <<TARGET_FILE<< std::endl;
#else	
	long fileSize = 0;
	FILE* fileSave;
	fileSave = fopen(TARGET_FILE, "wb+");


	while (stream->Read(&note)) {

		//stream->Write(note);
		fwrite((void*)note.datasend().c_str(), note.size(), 1, fileSave);
		fileSize += note.size();
		//std::cout << "GetMessage" << note.datasend().c_str() << "size:" << note.size() << std::endl;
	
	}
	fclose(fileSave);
	std::cout << "Get Target File " << "size:" << fileSize << std::endl;
#endif	

	char tempMsg[500];
	memset(tempMsg, '\0', 500);

	objPcl.InteractiveIcp((char*)TARGET_FILE, tempMsg);

	//std::cout << "Send to clinet:" << tempMsg << std::endl;
	server_note.set_datasend((void*)tempMsg, strlen(tempMsg));
	server_note.set_size(strlen(tempMsg));
	stream->Write(server_note);

	return Status::OK;
}

Status RouteGuideImpl::SetIcpMaxIterations(ServerContext* context, const IcpMaxIterationsRequest* request, IcpMaxIterationsReply* reply) {

	objPcl.SetMaxIterations(request->maxiterations());
	std::cout << "request->maxiterations(): " << request->maxiterations() << std::endl;
	reply->set_retsts(true);
	return Status::OK;
}

Status RouteGuideImpl::SetIcpFilter(ServerContext* context, const IcpFilterRequest* request, IcpFilterReply* reply) {

	objPcl.SetIcpFilter(request->filter());
	std::cout << "request->filter(): " << request->filter() << std::endl;
	reply->set_retsts(true);
	return Status::OK;
}


