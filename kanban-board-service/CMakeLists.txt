cmake_minimum_required(VERSION 3.16.0)
project(Prog3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# in case we want to build a static linked binary
#if(NOT CMAKE_SYSTEM_NAME MATCHES Darwin)
#  set(BUILD_SHARED_LIBS OFF)
#  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
#endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
include(CMakePrintHelpers)

# this adapts the library file suffixes, by default cmake does not recognize .dll on windows
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll" ".a")
# in case we cannot find package this is helpful to debug cmake search
# set(CMAKE_FIND_DEBUG_MODE 1)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.55 COMPONENTS system thread REQUIRED)

add_subdirectory(extern/crowcpp)
add_subdirectory(extern/rapidjson)
add_subdirectory(extern/sqlite)

add_subdirectory(src)

target_link_libraries(Service crow rapidjson sqlite3)
target_compile_definitions(Service PUBLIC "$<$<CONFIG:RELEASE>:RELEASE_SERVICE>")

if(WIN32)
  target_compile_options(Service PRIVATE -DBOOST_ERROR_CODE_HEADER_ONLY)
endif()


