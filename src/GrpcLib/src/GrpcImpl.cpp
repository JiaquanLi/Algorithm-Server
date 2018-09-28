/*
*
*  GrpcImpl.h
*
*/

#include"GrpcImpl.h"
#include "interactive_icp.h"



Status RouteGuideImpl::RouteChat(ServerContext* context,
                 ServerReaderWriter<RouteNote, RouteNote>* stream){
	std::vector<RouteNote> received_notes;

	FILE* fileSave;
	fileSave = fopen("Get.txt", "wb+");
	RouteNote server_note;
	RouteNote note;
	while (stream->Read(&note)) {
		//stream->Write(note);
		fwrite((void*)note.datasend().c_str(), note.size(), 1, fileSave);
		std::cout << "GetMessage" << note.datasend().c_str() << "size:" << note.size() << std::endl;
	}
	fclose(fileSave);

	char tempMsg[500];
	memset(tempMsg, '\0', 500);
	ApiPCL objPcl;
	objPcl.InteractiveIcp("Get.txt", "tempFileGrpc.txt", tempMsg);
	std::cout << "Send to clinet:" << tempMsg << std::endl;
	server_note.set_datasend((void*)tempMsg, strlen(tempMsg));
	server_note.set_size(strlen(tempMsg));
	stream->Write(server_note);

	return Status::OK;
}


