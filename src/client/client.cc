#include "client.h"
#include <network/requestCurl.h>
#include <parser/parser.h>

namespace soundcloud {

Client::Client(const std::string& clientID)
    : m_clientID(clientID)
{
}

std::vector<Track> Client::getTracks(const TracksQuery& query)
{
    requestCurl request(query.getURLString());
    requestCurl::SSLOps ops;
    ops.skip_peer_verification = true;
    request.setSSLOptions(ops);
    request.perform();
    Parser parser;
    return parser.parseTracks(request.getResponse());
}

}
