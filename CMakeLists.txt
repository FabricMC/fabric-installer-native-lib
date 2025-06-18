cmake_minimum_required(VERSION 3.17)

include(FetchContent)

if(APPLE)
    set (CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum X64 deployment version" FORCE)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Architectures" FORCE)
    set (CMAKE_XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET[arch=arm64] "11.0" CACHE STRING "Minimum ARM64 deployment version" FORCE)
endif()

project(fabric_installer_native_lib)

set(CMAKE_CXX_STANDARD 20)

set(NATIVE_SOURCE linux.cpp) # The source file to be build against the header
set(NATIVE_JNI linux) # The platform specific JNI sub directory
IF(APPLE)
    set(NATIVE_SOURCE macos.mm)
    set(NATIVE_JNI darwin)
ELSEIF (WIN32)
    set(NATIVE_SOURCE windows.cpp)
    set(NATIVE_JNI win32)
ENDIF()

message(STATUS "JAVA_HOME= $ENV{JAVA_HOME}")

set(JAVA_INCLUDE_PATH $ENV{JAVA_HOME}/include)
set(JAVA_INCLUDE_PATH2 $ENV{JAVA_HOME}/include/${NATIVE_JNI})
set(JAVA_AWT_LIBRARY NotNeeded)
set(JAVA_JVM_LIBRARY NotNeeded)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(fabric_installer_native_lib SHARED MojangLauncherHelper.h ${NATIVE_SOURCE})

if(WIN32)
  add_library(wil INTERFACE)

  FetchContent_Declare(
      microsoft_wil
      URL https://github.com/microsoft/wil/archive/refs/tags/v1.0.250325.1.zip
    )
  FetchContent_Populate(microsoft_wil)
  target_include_directories(wil INTERFACE ${microsoft_wil_SOURCE_DIR}/include)
  target_link_libraries(fabric_installer_native_lib PRIVATE wil)
endif()

IF(APPLE)
    target_link_libraries(fabric_installer_native_lib "-framework AppKit")
ENDIF()