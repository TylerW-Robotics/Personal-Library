cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("EE553 Final Project")

message (STATUS "[${PROJECT_NAME}] Processing ${CMAKE_CURRENT_LIST_FILE}")

add_executable(FinalProject src/main.cpp inc/personalLibrary.h src/personalLibrary.cpp src/textTool.cpp inc/textTool.h)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Personal_Library.csv ${CMAKE_CURRENT_BINARY_DIR} [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])

# file(CHMOD /src/Personal_Library.csv [PERSMISSIONS <OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, WORLD_READ, WORLD_WRITE, WORLD_EXECUTE, SETUID, SETGID?>])
