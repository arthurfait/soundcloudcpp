#include "client.h"
// #include "auth.h"
// #include <network/requestCurl.h>
// #include <parser/parser.h>


namespace soundcloud {

const std::string kSOUNDCLOUD_BASE_URL = "https://api.soundcloud.com";

Client::Client(const std::string& clientID)
    : m_clientID(clientID)
{
    // AuthDelegate auth(m_clientID);
    // auth.getAuthUrl();
}

std::shared_ptr<TracksRequest> Client::getTracks(const std::string& searchString,
                                const std::vector<std::string>& tagList,
                                const std::vector<std::string>& genres,
                                const uint32_t limit)
{
    TracksQuery query(kSOUNDCLOUD_BASE_URL, m_clientID, limit, searchString, tagList, genres);
    // std::cout << query.getURLString() << std::endl;
    return std::shared_ptr<TracksRequest>(new TracksRequest(query.getURLString()));
}

std::string Client::resolveTrackStream(const Track& track)
{
    return track.stream_url() + "?client_id=" +m_clientID;
}

}
