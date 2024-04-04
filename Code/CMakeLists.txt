cmake_minimum_required (VERSION 3.11)

set (CMAKE_CXX_STANDARD 17)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Server")

add_subdirectory(src)
add_subdirectory(include)

add_definitions(-DBOOST_ALL_NO_LIB)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Server)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "G:/Libs/boost_1_84_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "G:/Libs/boost_1_84_0/lib64-msvc-14.3")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.84.0 REQUIRED)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# show download progress
set(FETCHCONTENT_QUIET FALSE)

CPMAddPackage("gh:nlohmann/json@3.11.3")

include_directories(${CMAKE_SOURCE_DIR}/include/HTTP)
include_directories(${CMAKE_SOURCE_DIR}/include/Server)
include_directories(${CMAKE_SOURCE_DIR}/include/Client)
link_directories(${CMAKE_SOURCE_DIR}/src/Client)
link_directories(${CMAKE_SOURCE_DIR}/src/HTTP)
link_directories(${CMAKE_SOURCE_DIR}/src/Server)

add_library(
	HTTP
	include/HTTP/checks.hpp
	include/HTTP/HTTPDocument.hpp
	include/HTTP/HTTPHandler.hpp
	include/HTTP/HTTPHeader.hpp
	include/HTTP/HTTPParser.hpp
	include/HTTP/HTTPReply.hpp
	include/HTTP/HTTPReplyParser.hpp
	include/HTTP/HTTPRequest.hpp
	include/HTTP/HTTPRequestHandler.hpp
	include/HTTP/HTTPRequestParser.hpp
	include/HTTP/InvalidHTTPVersionException.hpp
	include/HTTP/HTTPSerializer.hpp
	include/HTTP/HTTPReplySerializer.hpp
	include/HTTP/Stock.hpp
	include/HTTP/Target.hpp
	include/HTTP/URIDecoder.hpp
	include/HTTP/HTTPReplyHandler.hpp
	include/HTTP/HTTPRequestSerializer.hpp
	include/HTTP/HTTPHeaderValueClass.hpp
	include/HTTP/HTTPHeaderValueClassField.hpp
	src/HTTP/checks.cpp
	src/HTTP/HTTPHandler.cpp
	src/HTTP/HTTPHeader.cpp
	src/HTTP/HTTPParser.cpp
	src/HTTP/HTTPReplyParser.cpp
	src/HTTP/HTTPRequestHandler.cpp
	src/HTTP/HTTPRequestParser.cpp
	src/HTTP/HTTPSerializer.cpp
	src/HTTP/HTTPReplySerializer.cpp
	src/HTTP/HTTPRequestSerializer.cpp
	src/HTTP/HTTPDocument.cpp
	src/HTTP/HTTPReply.cpp
	src/HTTP/URIDecoder.cpp
	src/HTTP/HTTPReplyHandler.cpp
	src/HTTP/InvalidHTTPVersionException.cpp
	src/HTTP/HTTPHeaderValueClass.cpp
	src/HTTP/HTTPHeaderValueClassField.cpp
	src/HTTP/Stock.cpp
)

target_include_directories(HTTP PRIVATE include/HTTP/)
target_include_directories(HTTP PRIVATE src/HTTP/)

add_executable(
	Server
	src/Server/main.cpp 
	include/Server/server.hpp 
	src/Server/server.cpp 
	include/Server/conection.hpp 
	src/Server/conection.cpp 
	include/Server/Configuration.hpp
	src/Server/Session.cpp
	include/Server/Session.hpp
	src/Server/SessionManager.cpp
	include/Server/SessionManager.hpp
	src/Server/DigestManager.cpp 
	include/Server/DigestManager.hpp
)

target_include_directories(Server PRIVATE include/Server)
target_link_libraries(Server PRIVATE HTTP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Client)

add_executable(
	Client
	src/Client/main.cpp 
	src/Client/CommandParcer.cpp
	src/Client/Client.cpp
	src/Client/CommandHandler.cpp
	src/Client/NoFileToPostException.cpp
	src/Client/CantOpenPostedFileException.cpp
	src/Client/InvalidTargetFormatException.cpp
	include/Client/Client.hpp 
	include/Client/command.hpp 
	include/Client/CommandParcer.hpp
	include/Client/CommandHandler.hpp
	include/Client/InvalidTargetFormatException.hpp
	include/Client/NoFileToPostException.hpp
	include/Client/CantOpenPostedFileException.hpp
	include/Client/Config.hpp
)

target_include_directories(Client PRIVATE include/Client)
target_link_libraries(Client PRIVATE HTTP)

target_link_libraries(HTTP nlohmann_json)