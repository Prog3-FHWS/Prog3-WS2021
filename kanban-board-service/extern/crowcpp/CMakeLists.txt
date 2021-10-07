add_library(crow INTERFACE)
target_include_directories(crow SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(crow INTERFACE Boost::system Boost::thread)

if(WIN32)
    target_link_libraries(crow INTERFACE "ws2_32" "wsock32")
endif()