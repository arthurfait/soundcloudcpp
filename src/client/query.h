#ifndef QUERY_H
#define QUERY_H

#include <string>

namespace soundcloud {

const std::string kSOUNDCLOUD_BASE_URL = "https://api.soundcloud.com";

class Query
{
public:
    Query(const std::string& baseURL,
          const std::string& clientID)
        : m_baseURL(baseURL)
        , m_clientID(clientID)
    {}

    virtual ~Query() {}

protected:
    std::string m_baseURL;
    std::string m_clientID;
};

class TracksQuery: public Query
{
public:
    TracksQuery(const std::string& baseURL,
                const std::string& clientID,
                const std::string& tag)
        : Query(baseURL, clientID)
        , m_tag(tag)
    {}

    virtual ~TracksQuery();

    std::string getURLString() const;
protected:
    // TODO: add all search ops
    std::string m_tag;
};

} // soundcloud

#endif // QUERY_H
