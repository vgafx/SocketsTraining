cmake_minimum_required(VERSION 2.8)

project(SocketsTraining)
set(CMAKE_CXX_FLAGS "-O3")

set(SOURCES
    main.cpp
    socket.cpp
    tcpsocket.cpp
    udpsocket.cpp
    socketexception.cpp
    tcpserversocket.cpp)

set(HEADERS
    socket.h
    tcpsocket.h
    udpsocket.h
    socketexception.h
    tcpserversocket.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
