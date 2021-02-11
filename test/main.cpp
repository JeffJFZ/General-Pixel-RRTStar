// DEMO by  SpeedyZJF

//#include "../include/zjfCommonHeader.h"
//#include "../include/uiFrame.h"
#include "nullDemoUi.h"
#include "FlowLayout.h"
#include <iostream>
#include <string.h>
#include "algoShell.h"


#ifdef _DEBUG
#pragma comment(lib, "AlgoNamed.lib")
#else
#pragma comment(lib, "AlgoName.lib")
#endif


int main(int argc, char* argv[])
{
	// TO DO BELOW

	std::cout << "Hello, world. --- test AlgoSDK." << std::endl;
	//QApplication qtApplication(argc, argv);
	int rtnCode = algoShellDemo(argc, argv);
	std::cout << "Running over." << std::endl;
	/*delete ptrCUiFrm;*/

	//return qtApplication.exec();
}
