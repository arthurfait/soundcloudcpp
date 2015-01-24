#ifndef TRACKPARSER_H
#define TRACKPARSER_H


#include <vector>
#include <string>
#include <json/json.h>
#include "types/track.h"

namespace soundcloud {

class Parser
{
public:
    Parser()
        : lastParsingSuccessful(false)
    {}
    ~Parser() {}

    std::vector<Track> parseTracks(const std::string& jsonData);

private:
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
};

} // soundcloud

#endif // TRACKPARSER_H
