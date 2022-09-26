#include <iostream>
#include <capnp/ez-rpc.h>
#include "myservice.capnp.h"
int main()
{
    std::cout << "Client" << std::endl;

    // Set up the EzRpcClient, connecting to the server on port
    // 5923 unless a different port was specified by the user.
    capnp::EzRpcClient client("localhost", 5923);
    auto &waitScope = client.getWaitScope();

    // Request the bootstrap capability from the server.
    MyService::Client cap = client.getMain<MyService>();

    // Make a call to the capability.
    auto request = cap.startRequest();
    request.setLevel(123);
    auto promise = request.send();

    // Wait for the result.  This is the only line that blocks.
    auto response = promise.wait(waitScope);

    // All done.
    std::cout << response.getSessionid() << std::endl;

    return 1;
}