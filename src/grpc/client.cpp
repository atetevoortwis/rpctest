#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "my.grpc.pb.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mygrpc::MyReply;
using mygrpc::MyRequest;
using mygrpc::MyService;

class MyServiceClient
{
public:
    MyServiceClient(std::shared_ptr<Channel> channel) : _stub(MyService::NewStub(channel))
    {
    }
    bool SayHello(const std::string& name)
    {
        ClientContext c;
        MyReply repl;
        MyRequest req;
        req.set_name(name);
        Status s = _stub->SayHello(&c, req, &repl);
        if (!s.ok())
        {
            std::cout << "RPC Error in SayHello" << std::endl;
            return false;
        }
        std::cout << "Reply: " << repl.message() << std::endl;

        return true;
    }

private:
    std::unique_ptr<MyService::Stub> _stub;
};

int main(int argc, const char* argv[])
{
    if(argc != 2){
        std::cout<<"Please supply a single argument"<<std::endl;
        return 0;
    }
    MyServiceClient c(grpc::CreateChannel("localhost:8888",
                                          grpc::InsecureChannelCredentials()));
    c.SayHello(argv[1]);
}