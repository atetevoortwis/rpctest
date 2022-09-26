cmake_minimum_required(VERSION 3.15)
project(my_project)
set(CMAKE_INSTALL_PREFIX ./install)

include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.42.0  # e.g v1.28.0
  GIT_SHALLOW 1
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

add_executable(my_exe ./src/main.cpp)
target_link_libraries(my_exe grpc++)