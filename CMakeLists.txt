cmake_minimum_required(VERSION 3.0.0)
project(asio_demo VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")

include(CTest)
enable_testing()

#include_directories(work/src/ceph/build/boost/)
FIND_LIBRARY(BOOST_LIB boost_coroutine boost_context boost_system /usr/lib/x86_64-linux-gnu/)
FIND_LIBRARY(AIO_LIB rt /usr/lib/x86_64-linux-gnu/)
FIND_LIBRARY(SSL_LIB ssl /usr/lib/x86_64-linux-gnu/)
FIND_LIBRARY(CRYPTO_LIB crypto /usr/lib/x86_64-linux-gnu/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
link_libraries(${BOOST_LIB} ${AIO_LIB} ${SSL_LIB} ${CRYPTO_LIB})

add_executable(asio_demo main.cpp s3_hmac.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
