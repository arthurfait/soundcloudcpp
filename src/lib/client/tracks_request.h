/*
 * @file            tracks_request.h
 * @author       Arthur Fait
 * @date          23.05.14
 */

#ifndef TRACKS_REQUEST_H
#define TRACKS_REQUEST_H

#include <string>
#include <types/track.h>
#include "query.h"

namespace soundcloud {

class TracksRequest {
public:
    TracksRequest(const std::string& query);
    ~TracksRequest() {}

    bool hasNext() {
        return m_hasNext;
    }
    std::vector<Track> next();

private:
    bool m_hasNext;
    std::string m_query;
};

} // soundcloud

#endif // TRACKS_REQUEST_H
