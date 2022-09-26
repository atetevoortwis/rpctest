find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_FILE my)
get_filename_component(my_proto "${CMAKE_CURRENT_SOURCE_DIR}/proto/${PROTO_FILE}.proto" ABSOLUTE)
get_filename_component(my_proto_path "${my_proto}" PATH)
message("${my_proto}")
set(_PROTOBUF_PROTOC /usr/local/bin/protoc)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
set(_PROTOBUF_LIBPROTOBUF libprotobuf.a)
set(_REFLECTION grpc++_reflection)
set(_GRPC_GRPCPP gRPC::grpc++)


# Generated sources
set(my_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.pb.cc")
set(my_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.pb.h")

set(my_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.grpc.pb.cc")
set(my_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_FILE}.grpc.pb.h")
add_custom_command(
      OUTPUT "${my_proto_srcs}" "${my_proto_hdrs}" "${my_grpc_srcs}" "${my_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${my_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${my_proto}"
      DEPENDS "${my_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
add_library(my_grpc_proto
                ${my_grpc_srcs}
                ${my_grpc_hdrs}
                ${my_proto_srcs}
                ${my_proto_hdrs})
target_link_libraries(my_grpc_proto PUBLIC
                        ${_REFLECTION}
                        ${_GRPC_GRPCPP}
                        ${_PROTOBUF_LIBPROTOBUF})

add_executable(client client.cpp)
target_link_libraries(client 
                        my_grpc_proto)

add_executable(server server.cpp)
target_link_libraries(server 
                        my_grpc_proto )