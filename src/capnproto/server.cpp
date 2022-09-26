#include <iostream>
#include <capnp/ez-rpc.h>
#include "myservice.capnp.h"
class MyServiceImpl final: public MyService::Server {
  // Implementation of the Calculator Cap'n Proto interface.

public:
  kj::Promise<void> start(StartContext context) override {
    context.getResults().setSessionid(123);
    return kj::READY_NOW;
  }
};
int main()
{
    std::cout << "Server" << std::endl;
    capnp::EzRpcServer server(kj::heap<MyServiceImpl>(), "localhost", 5923);
    auto &waitScope = server.getWaitScope();

    // Run forever, accepting connections and handling requests.
    kj::NEVER_DONE.wait(waitScope);
    return 1;
}