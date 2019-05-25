# CMake based build system.
cmake_minimum_required (VERSION 2.6)

# The project name
project (pdct)

#option
option ( enable-debug "enable debugging (default=off)" on )
option ( enable-debug-release "enable debugging release (default=off)" off )
option ( enable-release "enable release (default=on)" on )
option ( enable-log "enable log (default=off)" on )       

# The version number.
set (pdct_VERSION_MAJOR 0)
set (pdct_VERSION_MINOR 1)
set (pdct_VERSION_PATCH 1)
set (pdct_VERSION_BUILD 1)

# hardware acceleration
set ( GNUCC_HARDWARE_FLAGS "-msse4.2" )
set ( ENABLE_INT_SSE 1)
set ( ENABLE_ARM_NEON 0)
set ( HYPER_THREADING_COUNT 2)
set ( ENABLE_EMBEDDED 0)

# gcc setup
set ( GNUCC_WARNING_FLAGS "-Wall -Wextra" )

set ( CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-2 -DDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")
set ( CMAKE_C_FLAGS_DEBUG   "-g3 -gdwarf-2 -DDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")

set ( CMAKE_C_FLAGS_RELEASE   "-O3 -DNDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")
set ( CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")

set ( CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g -DNDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")
set ( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG ${GNUCC_HARDWARE_FLAGS} ${GNUCC_WARNING_FLAGS}")

# build type
if ( enable-debug )
    set ( CMAKE_BUILD_TYPE "Debug" CACHE STRING
          "Choose the build type, options: Debug Release RelWithDebInfo" FORCE )
elseif ( enable-debug-release )
    set ( CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
          "Choose the build type, options: Debug Release RelWithDebInfo" FORCE )
elseif ( enable-release )
    set ( CMAKE_BUILD_TYPE "Release" CACHE STRING
          "Choose the build type, options: Debug Release RelWithDebInfo" FORCE )
endif ( enable-debug )

if ( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE "Release" CACHE STRING
          "Choose the build type, options: Debug Release RelWithDebInfo" FORCE )
endif ( NOT CMAKE_BUILD_TYPE )

#enable logs
if ( enable-log )
set ( ENABLE_LOG 1)
endif ( enable-log )

# does this system provide the .... functions?
include(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(pthread pthread_create "<pthread.h>" HAVE_PTHREAD)
CHECK_LIBRARY_EXISTS(asound snd_seq_open "<alsa/asoundlib.h>" HAVE_ASOUND)

# wxwidgets file
find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/pdct_config.h.in"
  "${PROJECT_BINARY_DIR}/pdct_config.h"
  )
configure_file (
  "${PROJECT_SOURCE_DIR}/log_config.h.in"
  "${PROJECT_BINARY_DIR}/log_config.h"
  )
 
# Add the binary tree to the search path for include files
# so that we will find pdct_config.h
include_directories("${PROJECT_BINARY_DIR}")

# Add the library pdct_lib
include_directories ("${PROJECT_SOURCE_DIR}/pdct_lib")
add_subdirectory (pdct_lib)
include_directories (${INCLUDE_FOLDER})

# main executable
add_executable(pdct pdct_main.cpp)

target_link_libraries (pdct  pdct_lib asound pthread sndfile jack ${wxWidgets_LIBRARIES})

#install executable
install (TARGETS pdct DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${pdct_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${pdct_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${pdct_VERSION_PATCH}")
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrea Celani")
include (CPack)

# print info about compilation flags
message( STATUS "****CMAKE_BUILD_TYPE*****")
message( STATUS ">> " ${CMAKE_BUILD_TYPE} " <<")
if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
    message( STATUS "CMAKE_CXX_FLAGS_DEBUG:   " ${CMAKE_CXX_FLAGS_DEBUG} )
    message( STATUS "CMAKE_C_FLAGS_DEBUG:     " ${CMAKE_C_FLAGS_DEBUG} )
endif ( CMAKE_BUILD_TYPE MATCHES "Debug" )

if ( CMAKE_BUILD_TYPE MATCHES "Release" )
    message( STATUS "CMAKE_C_FLAGS_RELEASE:    " ${CMAKE_C_FLAGS_RELEASE} )
    message( STATUS "CMAKE_CXX_FLAGS_RELEASE:  " ${CMAKE_CXX_FLAGS_RELEASE} )
endif ( CMAKE_BUILD_TYPE MATCHES "Release" )

if ( CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
    message( STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO:   " ${CMAKE_C_FLAGS_RELWITHDEBINFO} )
    message( STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} )
endif ( CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" )
message( STATUS "*************************" )


#custom target for clean (used only by IDE)
add_custom_target(clean-cmake-files
   COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/clean-all.cmake
)
add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/clean-all.cmake
   COMMAND ${CMAKE_COMMAND} ..
)


