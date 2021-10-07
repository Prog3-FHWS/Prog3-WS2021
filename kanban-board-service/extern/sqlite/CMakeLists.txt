enable_language(C)
add_library(sqlite3 STATIC sqlite3.c)

target_include_directories(sqlite3 SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT MSVC)
    find_package(Threads REQUIRED)
    target_link_libraries(sqlite3 PUBLIC Threads::Threads ${CMAKE_DL_LIBS})
endif()
