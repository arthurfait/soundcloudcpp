#include "parser.h"
#include <iostream>

namespace soundcloud {

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

std::vector<Track> Parser::parseTracks(const std::string& jsonData)
{
    std::vector<Track> tracks;
    bool lastParsingSuccessful = reader.parse(jsonData, root);
    if (!lastParsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
                   << reader.getFormattedErrorMessages();
        return tracks;
    }
    if (root.type() == Json::arrayValue) {
        for (int i=0; i< root.size(); ++i) {
            if (root[i].type() == Json::objectValue) {
                if (root[i]["kind"].asString() == "track") {
                    tracks.push_back(trackFromJsonValue(root[i]));
                }
            }
        }
    }
    return tracks;
}


} // soundcloud
