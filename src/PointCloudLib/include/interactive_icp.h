
#ifndef INTERACTIVE_ICP_H_
#define INTERACTIVE_ICP_H_

class ApiPCL
{
	public:
		ApiPCL();
		~ApiPCL();
		bool InteractiveIcp(char* file1,char* file2,char* result);
	private:
			int iterations ;//= 100;  // Default number of ICP iterations
};

#endif
