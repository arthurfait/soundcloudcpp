/*
 * @file            tracks_request.h
 * @author       Arthur Fait
 * @date          23.05.14
 */

#ifndef TRACKS_REQUEST_H
#define TRACKS_REQUEST_H

#include <memory>
#include <string>
#include <types/track.h>
#include "query.h"

namespace soundcloud {

class requestCurl;
class Parser;

class TracksRequest {
public:
    TracksRequest(const std::string& query);
    ~TracksRequest();

    bool hasNext();
    uint32_t pageNumber() {
        return m_pageNumber;
    }
    std::vector<Track> next();

private:
    uint32_t m_pageNumber;
    std::string m_query;
    std::unique_ptr<requestCurl> m_request;
    std::unique_ptr<Parser> m_parser;
};

} // soundcloud

#endif // TRACKS_REQUEST_H
