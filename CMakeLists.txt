cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project("Personal Library")

message (STATUS "[${PROJECT_NAME}] Processing ${CMAKE_CURRENT_LIST_FILE}")

add_executable(FinalProject src/main.cpp inc/personalLibrary.h src/personalLibrary.cpp src/textTool.cpp inc/textTool.h)

set(csv_content "")

# Check if the CSV file exists
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/Personal_Library.csv)
  # Include the CSV file
  set(csv_content "")
  file(READ ${CMAKE_CURRENT_SOURCE_DIR}/src/Personal_Library.csv csv_content)
#else()
  # Create the CSV file
  #set(csv_content "")
  # set(csv_content "name,age\nJohn,25\nJane,30\n")
  #file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/Personal_Library.csv "${csv_content}")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Personal_Library.csv ${CMAKE_CURRENT_BINARY_DIR} [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
endif()


# file(CHMOD /src/Personal_Library.csv [PERSMISSIONS <OWNER_READ, OWNER_WRITE, OWNER_EXECUTE, GROUP_READ, GROUP_WRITE, GROUP_EXECUTE, WORLD_READ, WORLD_WRITE, WORLD_EXECUTE, SETUID, SETGID?>])
