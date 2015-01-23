#include <fstream>
#include <string>
#include <iostream>
#include <json/json.h>
#include "types/track.h"

using soundcloud::Track;

Track trackFromJsonValue(Json::Value& value)
{
    return Track(
                value["title"].asString(),
                value["description"].asString(),
                value["genre"].asString(),
                value["duration"].asInt(),
                value["stream_url"].asString(),
                value["license"].asString(),
                value["artwork_url"].asString(),
                value["waveform_url"].asString());
}

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

    std::cout << data << std::endl;

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( data, root );
    if (!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return -1;
    }
    if (root.type() == Json::arrayValue) {
        for (int i=0; i< root.size(); ++i) {
            if (root[i].type() == Json::objectValue) {
                if (root[i]["kind"].asString() == "track") {
                    std::cout << trackFromJsonValue(root[i]) << std::endl;
                }
            }
        }
    }

}
