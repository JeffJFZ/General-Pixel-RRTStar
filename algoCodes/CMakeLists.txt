##AlgoSDKUtilityFrame Created by SpeedyZJF.2018-2019.ZJU.Hangzhou.China.
INCLUDE(./ProjectPreConfig.cmake)
PROJECT(${ALGO_PROJ_NAME}) #V6.1, mainly aimed at Windows

#NOTE: version of cmake >= 3.5 && < 3.9
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
if(${CMAKE_MINOR_VERSION} GREATER 8)
	message(FATAL_ERROR "Warning: The version of CMAKE had better be less than 3.9.0 in view of the issue of encoding.
	I recommend the version 3.8.0.")
endif()

##------ Set a build type if none was specified -------
#skip that.

##----- ENV SETTING -----
#message(STATUS "ENV_PATH:$ENV{Path}")
set(ORIGIN_ENVS $ENV{Path})
#message(STATUS "ENVS:${ORIGIN_ENVS}")
SET(ENV3RDPATH ../Local3rdParty/fromMITK/bin)
FILE(GLOB ENV3RDFULLPATH "${ENV3RDPATH}")
#message(STATUS "ENV3RDFULLPATH: ${ENV3RDFULLPATH}")
LIST(APPEND ORIGIN_ENVS ${ENV3RDFULLPATH})
#message(STATUS "ENVS:${ORIGIN_ENVS}")
SET(ENV{Path} "${ORIGIN_ENVS}") #$ENV{Path};
#message(STATUS "ENV_PATH:$ENV{Path}")

#------ OpenMP below ------
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

##------ pthread below ------

### ------ ADD 3RD LIBS BELOW -------
##Additional include directories
FILE(GLOB children "../Local3rdParty/fromMITK/include/*")
set(SUBDIRS "")
foreach(child ${children})
	if(IS_DIRECTORY ${child})
		list(APPEND SUBDIRS ${child})
	endif()
endforeach()
#list(REMOVE_ITEM "*/opencv")
#list(REMOVE_ITEM "*/opencv2")
list(APPEND SUBDIRS "../Local3rdParty/fromMITK/include")
#list(APPEND SUBDIRS ../Local3rdParty/openCVSimpleImp)
INCLUDE_DIRECTORIES(${SUBDIRS})
message(STATUS "SETTING ADDITIONAL_INCLUDE_DIRECTORIES SUCCESSFULLY.")
#Additional library directories
link_directories(../Local3rdParty/fromMITK/lib/Debug ../Local3rdParty/fromMITK/lib/Release)
message(STATUS "SETTING ADDITIONAL_LIBRARY_DIRECTORIES SUCCESSFULLY.")

##------ cuda below ------
#project(test_cuda_project)
find_package(CUDA)
if(CUDA_FOUND)
#nvcc flags
set(CUDA_NVCC_FLAGS -gencode arch=compute_20, code=sm_20; -G; -g)
#message(STATUS "CUDA Found.")
endif()
#file()
#source_group("Include" FILES ${CUDA_CURRENT_HEADERS})
#source_group("Source" FILES ${CUDA_CURRENT_SOURCES})
#cuda_add_executable(test_cuda_project ${CUDA_CURRENT_SOURCES} ${CUDA_CURRENT_HEADERS})

##---------- SRC CODES----------
#[!NOTE!]:GLOB cannot aumatically check the addition or reduction of files.  
#[!NOTE!]:If the addition or reduction happens, please run cmake again.
#[!NOTE!]:Re-Cmake, without making any modifications on CMakeLists.txt.
FILE(GLOB SRC_FILES "src/*.c**") 
FILE(GLOB HEAD_FILES "include/*.h**") 

## ----------- execution -------------
include(CheckFunctionExists)
check_function_exists(printf HAVE_PRINTF)
set(CMAKE_DEBUG_POSTFIX "d")
#set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd")
set(CMAKE_MINSIZEREL_POSTFIX "_s")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sdk/Release)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sdk/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)

#add_custom_target(build-time-make-directory ALL command ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/sdk)

add_library(${PROJECT_NAME} SHARED ${HEAD_FILES} ${SRC_FILES})

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/bin")

#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})
#Additional dependencies
FILE(GLOB RELEASE_LIBS "../Local3rdParty/fromMITK/lib/Release/*.lib") 
FILE(GLOB DEBUG_LIBS "../Local3rdParty/fromMITK/lib/Debug/*d.lib")
foreach(_deb ${DEBUG_LIBS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} debug ${_deb})
endforeach()
foreach(_res ${RELEASE_LIBS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized ${_res})
endforeach()
# \\ {DEMO_LIBS} ${Glue} ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS}
message(STATUS "SETTING ADDITIONAL_DEPENDENCIES SUCCESSFULLY.")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


