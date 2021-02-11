##AlgoSDKUtilityFrame Created by SpeedyZJF.2018-2019.ZJU.Hangzhou.China.
INCLUDE(algoCodes/ProjectPreConfig.cmake)
PROJECT(${TESTSDK_PROJ_NAME}) #V6.1, mainly aimed at Windows

ADD_SUBDIRECTORY(algoCodes) 

set(CMAKE_INCLUDE_CURRENT_DIR OFF) 

#NOTE: version of cmake >= 3.5 && < 3.9
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
if(${CMAKE_MINOR_VERSION} GREATER 8)
	message(FATAL_ERROR "Warning: The version of CMAKE had better be less than 3.9.0 in view of the issue of encoding.
	I recommend the version 3.8.0.")
endif()

#------ Set a build type if none was specified -------
#if(WIN32)
#if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#	message(STATUS "Setting build type to 'Debug' as none was specified.")
#	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
#	# Set the possible values of build type for cmake-gui
#	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MiniSizeRel" "RelWithDebInfo")
#endif()
#endif()

#------ OpenMP below ------
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

##------ pthread below ------


#------ cuda below ------

#project(test_cuda_project)
find_package(CUDA)
if(CUDA_FOUND)
#nvcc flags
set(CUDA_NVCC_FLAGS -gencode arch=compute_20, code=sm_20; -G; -g)

#file()
#file()
#source_group("Include" FILES ${CUDA_CURRENT_HEADERS})
#source_group("Source" FILES ${CUDA_CURRENT_SOURCES})
#cuda_add_executable(test_cuda_project ${CUDA_CURRENT_SOURCES} ${CUDA_CURRENT_HEADERS})
endif()

# ----------- QT5 --------------
option(PROJ_USE_QT5 "Build the project with QT." OFF)

if(PROJ_USE_QT5)  
  find_package(Qt5Widgets)
  find_package(Qt5Core)
  find_package(Qt5Gui)
  
  if(Qt5Widgets_FOUND AND Qt5Core_FOUND AND Qt5Gui_FOUND)
  set(CMAKE_AUTOMOC ON)
  FILE(GLOB UI_FILES "ui/*.ui")
  FILE(GLOB RCC_FILES "resources/*.qrc")
  qt5_wrap_ui(WRAP_FILES ${UI_FILES})
  endif()
endif()

FILE(GLOB SRC_FILES "test/*.c**") 
FILE(GLOB HEAD_FILES "test/*.h**") 

# Qt support
if(PROJ_USE_QT5)
  find_package(Qt5Core ${PROJ_QT5_MINIMUM_VERSION} REQUIRED) # at least Core required
  if(Qt5Core_FOUND)
  get_target_property(_qmake_exec Qt5::qmake LOCATION)
  execute_process(COMMAND ${_qmake_exec} -query QT_INSTALL_BINS
    RESULT_VARIABLE _result
     OUTPUT_VARIABLE QT_BINARY_DIR
    ERROR_VARIABLE _error
  )
  string(STRIP "${QT_BINARY_DIR}" QT_BINARY_DIR)
  if(_result OR NOT EXISTS "${QT_BINARY_DIR}")
    message(FATAL_ERROR "Could not determine Qt binary directory: ${_result} ${QT_BINARY_DIR} ${_error}")
  endif()

  find_program(QT_HELPGENERATOR_EXECUTABLE
    NAMES qhelpgenerator qhelpgenerator-qt5 qhelpgenerator5
    PATHS ${QT_BINARY_DIR}
    NO_DEFAULT_PATH
  )

  find_program(QT_COLLECTIONGENERATOR_EXECUTABLE
    NAMES qcollectiongenerator qcollectiongenerator-qt5 qcollectiongenerator5
    PATHS ${QT_BINARY_DIR}
    NO_DEFAULT_PATH
  )

  find_program(QT_ASSISTANT_EXECUTABLE
    NAMES assistant assistant-qt5 assistant5
    PATHS ${QT_BINARY_DIR}
    NO_DEFAULT_PATH
  )

  find_program(QT_XMLPATTERNS_EXECUTABLE
    NAMES xmlpatterns
    PATHS ${QT_BINARY_DIR}
    NO_DEFAULT_PATH
  )

  mark_as_advanced(QT_HELPGENERATOR_EXECUTABLE
                   QT_COLLECTIONGENERATOR_EXECUTABLE
                   QT_ASSISTANT_EXECUTABLE
                   QT_XMLPATTERNS_EXECUTABLE
                  )

  endif()
endif()

## ----------- 3rd Libs -----------
#----- ENV SETTING -----
SET(DLL_RELEASE_PATH ${CMAKE_BINARY_DIR}/bin/Release)
FILE(GLOB DLL_RELEASE_FULL_PATH "${DLL_RELEASE_PATH}")
#message(STATUS "DLL_RELEASE_FULL_PATH: ${DLL_RELEASE_FULL_PATH}")
set(ORIGIN_ENVS $ENV{Path})
#message(STATUS "ENVS:${ORIGIN_ENVS}")
LIST(APPEND ORIGIN_ENVS ${DLL_RELEASE_FULL_PATH})
SET(ENV{PATH} "${ORIGIN_ENVS}")
#message(STATUS "ENV_PATH:$ENV{PATH}")
SET(DLL_DEBUG_PATH ${CMAKE_BINARY_DIR}/bin/Debug)
FILE(GLOB DLL_DEBUG_FULL_PATH "${DLL_DEBUG_PATH}")
#message(STATUS "DLL_DEBUG_FULL_PATH: ${DLL_DEBUG_FULL_PATH}")
LIST(APPEND ORIGIN_ENVS ${DLL_DEBUG_FULL_PATH})
SET(ENV{PATH} "${ORIGIN_ENVS}")
#message(STATUS "ENV_PATH:$ENV{PATH}")

#// another method
file(GLOB _3RD_DLLS "./Local3rdParty/fromMITK/bin/*.dll")
file(COPY ${_3RD_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

#foreach（_dll ${_3RD_DLLS}）
# add_custom_command（TARGET MyTarget PRE_BUILD 
# COMMAND $ {CMAKE_COMMAND} -E 
# copy $ {ConfigFile} $< TARGET_FILE_DIR：MyTarget>）
#endforeach（）


#Additional include directories
FILE(GLOB subdirs "Local3rdParty/fromMITK/include/*")
#LIST(REMOVE_ITEM subdirs "*/opencv")
#LIST(REMOVE_ITEM subdirs "*/opencv2")
LIST(APPEND subdirs "Local3rdParty/fromMITK/include")
#LIST(APPEND subdirs Local3rdParty/openCVSimpleImp) #./ current directory
LIST(APPEND subdirs algoCodes/include)
INCLUDE_DIRECTORIES(${subdirs})
#Additional library directories
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
link_directories(./Local3rdParty/fromMITK/lib/Debug 
				./Local3rdParty/fromMITK/lib/Release 
				${CMAKE_BINARY_DIR}/bin/Release
				${CMAKE_BINARY_DIR}/bin/Debug)

FILE(GLOB _RELEASE_LIBS "./Local3rdParty/fromMITK/lib/Release/*.lib") 
FILE(GLOB _DEBUG_LIBS "./Local3rdParty/fromMITK/lib/Debug/*d.lib")

set(debugLibs "")
foreach(_deb_ ${_DEBUG_LIBS})
	list(APPEND debugLibs ${_deb_})
endforeach()

set(releaseLibs "")
foreach(_res_ ${_RELEASE_LIBS})
	list(APPEND releaseLibs ${_res_})
endforeach()

## ----------- execution -------------
include(CheckFunctionExists)
check_function_exists(printf HAVE_PRINTF)

if (Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Widgets_FOUND)
add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SRC_FILES} ${RCC_FILES} ${WRAP_FILES})
target_link_libraries(${PROJECT_NAME} optimized ${CMAKE_BINARY_DIR}/bin/Release/${ALGO_PROJ_NAME}.lib)
foreach(res ${releaseLibs})
target_link_libraries(${PROJECT_NAME} optimized ${res}) # Qt5::Widgets Qt5::Core Qt5::Gui
endforeach()
target_link_libraries(${PROJECT_NAME} optimized Qt5::Widgets Qt5::Core Qt5::Gui) # Qt5::Widgets Qt5::Core Qt5::Gui

target_link_libraries(${PROJECT_NAME} debug ${CMAKE_BINARY_DIR}/bin/Debug/${ALGO_PROJ_NAME}d.lib) 
foreach(deb ${debugLibs})
target_link_libraries(${PROJECT_NAME} debug ${deb}) 
endforeach()
target_link_libraries(${PROJECT_NAME} debug Qt5::Widgets Qt5::Core Qt5::Gui) 

else()

add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} optimized ${CMAKE_BINARY_DIR}/bin/Release/${ALGO_PROJ_NAME}.lib)
foreach(res ${releaseLibs})
target_link_libraries(${PROJECT_NAME} optimized ${res}) # Qt5::Widgets Qt5::Core Qt5::Gui
endforeach()
target_link_libraries(${PROJECT_NAME} debug ${CMAKE_BINARY_DIR}/bin/Debug/${ALGO_PROJ_NAME}d.lib) 
foreach(deb ${debugLibs})
target_link_libraries(${PROJECT_NAME} debug ${deb}) 
endforeach()
endif()

## ------ Set the dependency of projects ------
# access the project_name of .dll
target_link_libraries(${PROJECT_NAME} ${ALGO_PROJ_NAME})

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#file(GLOB sdkRes "${CMAKE_BINARY_DIR}/bin/Release/${PROJECT_NAME}.*")
#FILE(COPY ${sdkRes} DESTINATION ${CMAKE_BINARY_DIR}/sdk/Release)
#file(GLOB sdkDeb "${CMAKE_BINARY_DIR}/bin/Debug/${PROJECT_NAME}d.*")
#FILE(COPY ${sdkDeb} DESTINATION ${CMAKE_BINARY_DIR}/sdk/Debug)
#ADD_EXECUTABLE(${PROJECT_NAME} zjfCommonHeader.h DynamicPGSSolver_V6.3.cpp)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} #{DEMO_LIBS} ${Glue} ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS})
