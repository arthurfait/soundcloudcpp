/*
 * @file            tracks_request.cc
 * @author       Arthur Fait
 * @date          23.05.14
 */

#include "tracks_request.h"
#include <network/requestCurl.h>
#include <parser/parser.h>

namespace soundcloud {


TracksRequest::TracksRequest(const std::string& query)
    : m_hasNext(true)
    , m_query(query)
{}

std::vector<Track> TracksRequest::next()
{
    requestCurl request(m_query);
    requestCurl::SSLOps ops;
    ops.skip_peer_verification = true;
    request.setSSLOptions(ops);
    request.perform();
    Parser parser;
    return parser.parseTracks(request.getResponse());
}

} // soundcloud
