/* Copyright(c) by SpeedyZJF. All rights reserved. 
   Jeff.JFZ. ZJU.hangzhou	*/

#include "../include/zjfCommonHeader.h"

#ifdef _WIN32 
//32-bit and 64-bit, this part(_WIN32) is common. _WIN32 is always defined.

std::string rtnStrVSVersion(const int& versionCode)
{
	std::string strVSVersion;
	std::cout << "_MSC_VER = " << versionCode << std::endl;
#if _MSC_VER >= 1500
	//#pragma comment( lib, "RelatedHigher.lib" )
	// Calling some functions varying with different MSCs.
#else
	//#pragma comment( lib, "RelatedLower.lib" )
#endif
#if 1
	if (versionCode >= 1910 && versionCode < 1920) {
		strVSVersion = "VS2017";
	}
	// or make a map;
	switch (versionCode)
	{
	case 1900:
		//#pragma comment( lib, "RelatedHigher.lib" )
		strVSVersion = "VS2015"; break;
	case 1800:
		strVSVersion = "VS2013"; break;
	case 1700:
		strVSVersion = "VS2012"; break;
	case 1600:
		strVSVersion = "VS2010"; break;
	case 1500:
		strVSVersion = "VS2008"; break;
	case 1400:
		strVSVersion = "VS2005"; break;
	case 1310:
		strVSVersion = "VS2003"; break;
	case 1300:
		strVSVersion = "VS2002"; break;
	case 1200:
		strVSVersion = "VC++6.0"; break;
	default:
		strVSVersion = "Other versions. Pls check the _MSC_VER";
		break;
	}
#else
	if (versionCode >= 1910 && versionCode < 1920) {
		strVSVersion = "VS2017";
	}
	map<int, string> mapVSVersion;
	mapVSVersion.insert(pair<int, string>(1900, "VS2015"));
	mapVSVersion.insert(pair<int, string>(1800, "VS2013"));
	mapVSVersion.insert(pair<int, string>(1700, "VS2012"));
	mapVSVersion.insert(pair<int, string>(1600, "VS2010"));
	mapVSVersion.insert(pair<int, string>(1500, "VS2008"));
	mapVSVersion.insert(pair<int, string>(1400, "VS2005"));
	mapVSVersion.insert(pair<int, string>(1310, "VS2003"));
	mapVSVersion.insert(pair<int, string>(1300, "VS2002"));
	mapVSVersion.insert(pair<int, string>(1200, "VC++6.0"));
	map<int, string>::iterator iter;
	iter = mapVSVersion.find(versionCode);
	if (iter != mapVSVersion.end()) {
		strVSVersion = iter->second;
	}
	else {
		strVSVersion = "Other versions. Pls check the _MSC_VER";
	}

#endif

	return strVSVersion;
}

int getVSVersionCode()
{
	int ver = _MSC_VER;
	return ver;
}

WORD saveWinCurrentForeClr()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD currentClrAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;

	GetConsoleScreenBufferInfo(hConsole, &csbInfo);
	currentClrAttrs = csbInfo.wAttributes;
	return currentClrAttrs;
}

void setCmdWindowForegroundClr(FOREWINCOLORS foreColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreColor);
}

bool restoreWinDefaultForeClr(const WORD& defaultClr)
{
	//setCmdWindowForegroundClr(defaultClr);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, defaultClr);
	return true;	/// bool or void, just for fun, or a simple test.
}


#elif __linux__

void setLinuxForeColor(LINUXFORECOLORS linuxForeClr)
{
	/*char tmpClrStr[8];
	int tmpClrStrLength = sprintf(tmpClrStr, "%d", linuxForeClr);
	std::stringstream wholeClrStr;
	wholeClrStr << "\033[" << tmpClrStr << "m";
	std::cout << wholeClrStr << std::endl;*/

	std::cout << "\033[" << linuxForeClr << "m" << std::endl;
}
void restoreLinuxDefaultForeClr()
{
	std::cout << LINUXFORECLRDEFAULT << std::endl;
}

#endif

void dspCommonCurrentSysTime()
{
	/// Win && Linux
	struct tm *t;
	time_t localT;
	time(&localT);
	t = localtime(&localT);
	printf("CurrentTime: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}


#if _ARRAY23_DEMO_TST_
/// Two-dimensional Array(Mat) 
uInt numLine2, numCol2;	// uInt imgWidth, imgHeight;
float *TWOARRAYDEMO;
#define TWOARRAYDEMO(x,y) TWOARRAYDEMO[(x)*numLine2+y]
/// Three-dimensional Array(Tensor)
uInt numLine3, numCol3, numSlice3;	// uInt imgWidth, imgHeight, imgLayer/*imgSlice or imgFrame*/;
float *THREEARRAYDEMO;
#define THREEARRAYDEMO(x,y,z) THREEARRAYDEMO[(z)*numLine3*numCol3+ (x)*numLine3+y]

bool funcDefineArrayTst(const uInt& numLine, const uInt& numCol, const uInt& numSlice)
{
	TWOARRAYDEMO = (float *)malloc(sizeof(float)*numLine*numCol);
	THREEARRAYDEMO = (float *)malloc(sizeof(float)*numLine*numCol*numSlice);

#if 1
	for (uInt idx = 0; idx < numLine; ++idx) {
		for (uInt idy = 0; idy < numCol; ++idy) {
			TWOARRAYDEMO(idx, idy) = 201901;
		}
	}

	for (uInt idz = 0; idz < numSlice; ++idz) {
		for (uInt idx = 0; idx < numLine; ++idx) {
			for (uInt idy = 0; idy < numCol; ++idy) {
				THREEARRAYDEMO(idx, idy, idz) = 201902;
			}
		}
	}
#endif
	/// Check
	COUT << "Out1: " << ENDL;
	for (uInt idx = 0; idx < numLine; ++idx) {
		for (uInt idy = 0; idy < numCol; ++idy) {
			COUT << "[" << idx << ", " << idy << ", " << TWOARRAYDEMO(idx, idy) << "] ";
		}
		COUT << ENDL;
	}
	COUT << "Out2: " << ENDL;
	for (uInt idz = 0; idz < numSlice; ++idz) {
		for (uInt idx = 0; idx < numLine; ++idx) {
			for (uInt idy = 0; idy < numCol; ++idy) {
				COUT << "[" << idx << ", " << idy << ", " << idz << ", " << THREEARRAYDEMO(idx, idy, idz) << "] ";
			}
			COUT << ENDL;
		}
		COUT << ENDL;
	}

	free(TWOARRAYDEMO);
	free(THREEARRAYDEMO);

	return true;
}

#endif