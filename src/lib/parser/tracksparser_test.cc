#include <fstream>
#include <string>
#include <iostream>
#include "parser.h"

int main(int argc, char* argv[])
{
    std::string inputFileName = "o.js";
    // if (argv > 1)

    std::ifstream ifs (inputFileName, std::ifstream::in);
    std::string data;
    while(ifs.good()) {
        std::string line;
        ifs >> line;
        data.append(line);
    }

    // std::cout << data << std::endl;
    soundcloud::Parser parser;
    auto tracks = parser.parseTracks(data);
    for (const auto& track: tracks) {
        std::cout << track;
    }
}
