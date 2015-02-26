#include "parser.h"
#include <iostream>

namespace soundcloud {

User userFromJsonValue(Json::Value& value)
{
    return User(
                value["username"].asString(),
                value["permalink_url"].asString(),
                value["avatar_url"].asString(),
                value["uri"].asString(),
                value["id"].asUInt64()
        );
}

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
                value["waveform_url"].asString(),
                userFromJsonValue(value["user"]));
}

void collectTracks(Json::Value& value, std::vector<Track>& tracks)
{
    for (unsigned i=0; i< value.size(); ++i) {
        if (value[i].type() == Json::objectValue) {
            if (value[i]["kind"].asString() == "track") {
                tracks.push_back(trackFromJsonValue(value[i]));
            }
        }
    }
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
        collectTracks(root, tracks);
    } else {
        if (root.isMember("collection") && root["collection"].isArray()) {
            collectTracks(root["collection"], tracks);
            if (root.isMember("next_href")) {
                m_lastNextHref = root["next_href"].asString();
            } else {
                m_lastNextHref.clear();
            }
        }
    }

    return tracks;
}


} // soundcloud
