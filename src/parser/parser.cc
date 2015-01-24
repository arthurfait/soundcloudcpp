#include "parser.h"

namespace soundcloud {


std::vector<Track> Parser::parseTracks(const std::string& jsonData)
{
    bool lastParsingSuccessful = reader.parse(data, root);

}

private:
    bool lastParsingSuccessful;
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
};

} // soundcloud
