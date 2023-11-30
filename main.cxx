#include <memory>
#include <iostream>
#include "easycurl/easycurl.hxx"

auto testGet () -> void {

    //use smart pointers
    std::unique_ptr<Get> request (new Get("http://127.0.0.1:8000/get"));

    request->setParams("token", "1234-abcd-5678-efgh");

    //send get request
    request->fetch();

    //get responses from fetch
    std::cout << request->getResponse() << '\n';
    std::cout << request->getHeaders() << '\n';
    std::cout << request->getLength() << '\n';
    std::cout << request->getStatusCode() << '\n';

}

auto testPost () -> void {

    //use smart pointers
    std::unique_ptr<Post> request (new Post("http://127.0.0.1:8000/post"));

    request->setData("{\"key\":\"value\"}");
    //send post request
    request->fetch();

    //get responses from fetch
    std::cout << request->getResponse() << '\n';
    std::cout << request->getHeaders() << '\n';
    std::cout << request->getLength() << '\n';
    std::cout << request->getStatusCode() << '\n';

}

auto main ( int args, const char* params[] ) -> int {

    testGet();

    return 0x00;
}