// =================================================
// zjfCommonHeader.hpp designed by Speeedy.ZJF, 
// Ver 6.2+, 2019.03
// jfsufengATgmail.com || jfsufengATfoxmail.com
// =================================================
#pragma once	// Only for MS-VS-Series IDE
#ifndef _ZJFCOMMONHEADER_H_
#define _ZJFCOMMONHEADER_H_

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef __cplusplus
}
#endif // __cplusplus

#include <string>
//#include <map>

//// Some General Define below
#define FORLOOP(A,_SIZE) for(int idx=0;idx<_SIZE;idx++){A;}

#define COUT std::cout
#define ENDL std::endl

using namespace std;

typedef unsigned int uInt;
typedef const uInt cuInt;
typedef unsigned long long uLLong;

#ifdef _WIN32 
//32-bit and 64-bit, this part(_WIN32) is common. _WIN32 is always defined.
#include <Windows.h>
/*the used original IDE:VS2015, for this program*/
std::string rtnStrVSVersion(const int& versionCode);

int getVSVersionCode();

enum FOREWINCOLORS
{
	/// windows cmd
	BLUE = 9, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};

WORD saveWinCurrentForeClr();

void setCmdWindowForegroundClr(FOREWINCOLORS foreColor);

bool restoreWinDefaultForeClr(const WORD& defaultClr);

#ifdef _WIN64
#ifdef _DEBUG
#define RUNMODE "Debug Mode x64:"
#else
#define RUNMODE "Release Mode x64:"
#endif
#else
#ifdef _DEBUG
#define RUNMODE "Debug Mode x86:"
#else
#define RUNMODE "Release Mode x86:"
#endif
#endif

#elif __APPLE__
#define RUNMODE "Apple Platform Test:"
#include "TargetConditionals.h"
#ifdef TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif

#elif __linux__
#define RUNMODE "Linux Platform Test:"
#define LINUXFORECLRDEFAULT "\033[0m"
enum LINUXFORECOLORS
{
	RED = 31, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
};
void setLinuxForeColor(LINUXFORECOLORS linuxForeClr);
void restoreLinuxDefaultForeClr();
#elif __unix__ // all unices not caught above
#define RUNMODE "Unix Platform Test:"
#elif defined(_POSIX_VERSION)
// POSIX
#define RUNMODE "POSIX Platform Test:"
#else
#error "Unknown compiler"
#endif

void dspCommonCurrentSysTime();

#define _ARRAY23_DEMO_TST_ 2019
#if _ARRAY23_DEMO_TST_
/// Two-dimensional Array(Mat) 
extern uInt numLine2, numCol2;	// uInt imgWidth, imgHeight;
extern float *TWOARRAYDEMO;
#define TWOARRAYDEMO(x,y) TWOARRAYDEMO[(x)*numLine2+y]
/// Three-dimensional Array(Tensor)
extern uInt numLine3, numCol3, numSlice3;	// uInt imgWidth, imgHeight, imgLayer/*imgSlice or imgFrame*/;
extern float *THREEARRAYDEMO;
#define THREEARRAYDEMO(x,y,z) THREEARRAYDEMO[(z)*numLine3*numCol3+ (x)*numLine3+y]
bool funcDefineArrayTst(const uInt& numLine = 0, const uInt& numCol = 0, const uInt& numSlice = 0);
#endif

#endif