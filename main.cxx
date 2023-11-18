#include <memory>
#include <iostream>
#include "easycurl/get.hxx"

int main(){

    //use smart pointers
    std::unique_ptr<Get> request (new Get("http://127.0.0.1:8000/"));

    request->setParams("token", "1234-abcd-5678-efgh");

    //send get request
    request->fetch();

    //get responses from fetch
    std::cout << request->getResponse() << '\n';
    std::cout << request->getHeaders() << '\n';
    std::cout << request->getLength() << '\n';
    std::cout << request->getStatusCode() << '\n';


}