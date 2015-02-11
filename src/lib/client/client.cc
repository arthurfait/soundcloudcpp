#include "client.h"
// #include <network/requestCurl.h>
// #include <parser/parser.h>


namespace soundcloud {

const std::string kSOUNDCLOUD_BASE_URL = "https://api.soundcloud.com";

Client::Client(const std::string& clientID)
    : m_clientID(clientID)
{
}

TracksRequest Client::getTracks(const std::string& searchString,
                                const std::vector<std::string>& tagList,
                                const uint32_t limit)
{
    TracksQuery query(kSOUNDCLOUD_BASE_URL, m_clientID, 0, searchString, tagList);
    std::cout << query.getURLString() << std::endl;
    return TracksRequest(query.getURLString());
}

}
