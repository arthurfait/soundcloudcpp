/*
 * @file            tracks_request.cc
 * @author       Arthur Fait
 * @date          23.05.14
 */

#include <network/requestCurl.h>
#include <parser/parser.h>
#include "tracks_request.h"


namespace soundcloud {


TracksRequest::TracksRequest(const std::string& query)
    : m_pageNumber(0)
    , m_query(query)
    , m_request(nullptr)
    , m_parser(new Parser())
{
    m_request.reset(new requestCurl(m_query));
    requestCurl::SSLOps ops;
    ops.skip_peer_verification = true;
    m_request->setSSLOptions(ops);
}

TracksRequest::~TracksRequest()
{}

bool TracksRequest::hasNext()
{
    return !m_parser->lastNextHref().empty();
}

std::vector<Track> TracksRequest::next()
{
    if (m_pageNumber != 0) {
        if (hasNext()) {
            m_request->setURL(m_parser->lastNextHref());
        } else {
            return std::vector<Track>();
        }
    }
    m_pageNumber++;
    m_request->perform();
    return m_parser->parseTracks(m_request->getResponse());
}

} // soundcloud
