#include <libfasthttpserver/parsers/requestparser/requestparser.h>

#include <string>
#include <iostream>

int main() {
    // Test http request string
    std::string request = "GET / HTTP/1.1\r\nSome-Header: Some-Value\r\nAnother-Header: some,more,values\r\n\r\n";


    return 0;
}