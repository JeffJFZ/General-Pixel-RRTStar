// DEMO by SpeedyZJF
/*.h files Demo Created by SpeedyZJF*/
//// Std C Shell ////

enum ALLRETURN
{
	ERR_NONE = 399,		
	ERR_NULL,			
	ERR_PARAM,			
	ERR_SIZE,			
	ERR_MEMORY,			
	ERR_OTHERS			
};

#if defined(_WIN32) && !defined(__CYGWIN__)
#define DLL_EXPORT __declspec(dllexport)

enum WINFORECOLORS
{
	/// windows cmd
	BLUE = 9, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};
#else
#define DLL_EXPORT
#ifdef __linux__
enum LINUXFORECOLORS
{
	RED = 31, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
};
#endif
#endif 

DLL_EXPORT int algoShellDemo(int argc, char* argv[]);

