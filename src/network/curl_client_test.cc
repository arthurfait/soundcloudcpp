#include "requestCurl.h"
#include <iostream>

int main()
{
    const std::string url("https://api.soundcloud.com/tracks?client_id=a5a98f5d549a83896d565f69eb644b65&limit=10");
    const std::string url_1("https://api.soundcloud.com/tracks?client_id=a5a98f5d549a83896d565f69eb644b65&limit=10&tag=vocal%20dubstep");
    soundcloud::requestCurl request(url);
    soundcloud::requestCurl::SSLOps ops;
    ops.skip_peer_verification = true;
    request.setSSLOptions(ops);
    request.perform();
    std::cout << request.getResponse() << std::endl;
    std::cout << "second request:\n";
    request.setURL(url_1);
    request.perform();
    std::cout << request.getResponse() << std::endl;
    return 0;
}
