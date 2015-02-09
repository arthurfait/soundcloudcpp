#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include <types/track.h>
#include "query.h"

namespace soundcloud {

class Client
{
public:
    Client(const std::string& clientID);
    virtual ~Client() {}

    std::vector<Track> getTracks(const TracksQuery& query);

private:

    std::string m_clientID;
};

} // soundcloud

#endif // CLIENT_H
