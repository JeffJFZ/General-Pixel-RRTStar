// DEMO by SpeedyZJF

#include "../include/algoShell.h"
#include "../include/nullDemoAlgo.h"
#include "../include/nullDemoMid.hpp"

#ifdef __cplusplus
extern "C" {	// C linkage
#endif
#include "../include/nullDemoStdC.h"
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#include <iostream>

int algoShellDemo(int argc, char* argv[]) 
{
	std::cout<<"AlgoRD.\n-DLL_EXPORT-"<< std::endl;
	
	demoAlgo::className *ptr = new demoAlgo::className(argv[0]);
	ptr->itkTestFunc();
	delete ptr;
	return 0;
}