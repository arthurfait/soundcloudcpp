#include "client.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    // TODO: read from config
    const std::string kClientID = "a5a98f5d549a83896d565f69eb644b65";
    soundcloud::Client client(kClientID);

    auto tracks = client.getTracks(soundcloud::TracksQuery(
                                                    soundcloud::kSOUNDCLOUD_BASE_URL,
                                                    kClientID,
                                                    "vocal"));
    for (const auto& track: tracks) {
        std::cout << track;
    }


    return 0;
}
