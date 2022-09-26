#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "my.grpc.pb.h"
using mygrpc::MyReply;
using mygrpc::MyRequest;
class MyServiceImpl final : public mygrpc::MyService::Service
{
public:
    grpc::Status SayHello(grpc::ServerContext *context, const MyRequest *req, MyReply *reply) override
    {
        reply->set_message("Hello "+req->name());
        
        return grpc::Status::OK;
    }
};
int main()
{
    MyServiceImpl service;
    grpc::ServerBuilder builder;
    std::string address = "0.0.0.0:8888";
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listerning on "<<address<<std::endl;
    server->Wait();
    
    std::cout << "Hello" << std::endl;
    return 1;
}