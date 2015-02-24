#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include "query.h"
#include "tracks_request.h"

namespace soundcloud {

class Client
{
public:
    Client(const std::string& clientID);
    virtual ~Client() {}

    std::shared_ptr<TracksRequest> getTracks(const std::string& searchString,
                            const std::vector<std::string>& tagList,
                            const uint32_t limit);

    std::string resolveTrackStream(const Track& track);

private:

    std::string m_clientID;
};

} // soundcloud

#endif // CLIENT_H
