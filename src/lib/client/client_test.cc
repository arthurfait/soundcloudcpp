#include "client.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    // TODO: read from config
    const std::string kClientID = "a5a98f5d549a83896d565f69eb644b65";
    soundcloud::Client client(kClientID);


    std::vector<std::string> taglist = {"vocal"};
    soundcloud::TracksRequest tracksReq = client.getTracks("", taglist, 0);
    auto tracks = tracksReq.next();

    for (const auto& track: tracks) {
        std::cout << track;
    }


    return 0;
}
