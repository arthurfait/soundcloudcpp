#ifndef TRACKPARSER_H
#define TRACKPARSER_H

#include <json/json.h>
#include "types/track.h"

namespace soundcloud {

class Parser
{
public:
    Parser();
    ~Parser();

    std::vector<Track> parseTracks(std::string);

private:
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
};

} // soundcloud

#endif // TRACKPARSER_H
