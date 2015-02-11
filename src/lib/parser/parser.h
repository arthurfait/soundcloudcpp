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
        , m_lastNextHref("")
    {}
    ~Parser() {}

    const std::string& lastNextHref() const {
        return m_lastNextHref;
    }

    std::vector<Track> parseTracks(const std::string& jsonData);

private:
    bool lastParsingSuccessful;
    std::string m_lastNextHref;
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
};

} // soundcloud

#endif // TRACKPARSER_H
