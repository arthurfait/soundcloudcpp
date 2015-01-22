#include <fstream>
#include <string>
#include <iostream>
#include <json/json.h>

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
                    std::cout << "duration: " << root[i]["duration"].asInt()/1000<< " seconds" << std::endl;
                    std::cout << "genre: " << root[i]["genre"].asString() << std::endl;
                    std::cout << "title: " << root[i]["title"].asString() << std::endl;
                    std::cout << "stream_url: " << root[i]["stream_url"].asString() << std::endl;
                    std::cout << "license: " << root[i]["license"].asString() << std::endl;
                    std::cout << "artwork_url: " << root[i]["artwork_url"].asString() << std::endl;
                    std::cout << "waveform_url: " << root[i]["waveform_url"].asString() << std::endl;
                    std::cout << "description: " << root[i]["description"].asString() << std::endl;
                }
            }
        }
    }

}
