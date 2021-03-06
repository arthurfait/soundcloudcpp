#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>

namespace soundcloud {

class Query
{
public:
    Query(const std::string baseURL,
          const std::string clientID,
          const uint32_t limit)
        : m_baseURL(baseURL)
        , m_clientID(clientID)
        , m_limit(limit)
    {}
    virtual ~Query() {}

protected:
    std::string m_baseURL;
    std::string m_clientID;
    uint32_t m_limit;
};


class TracksQuery: public Query
{
public:
/** Construct TracksQuery object
 *
 * @param baseURL API URL
 * @param clientID client id for SoundCloud
 * @param limit maximum number of tracks(up to  200)
 * @param searchString generic search string
 * @param tagList vector with tags
 * @param genres vector with genres
 */
    TracksQuery(const std::string baseURL,
                const std::string clientID,
                const uint32_t limit,
                const std::string& searchString,
                const std::vector<std::string>& tagList,
                const std::vector<std::string>& genres

                // filter  enumeration (all,public,private)
                // bpm[from]   number  return tracks with at least this bpm value
                )
        : Query(baseURL, clientID, limit)
        , m_searchString(searchString)
        , m_tagList(tagList)
        , m_genres(genres)
    {}

    virtual ~TracksQuery() {}

    std::string getURLString() const;
protected:
    // TODO: add all search ops
    std::string m_searchString;
    std::vector<std::string> m_tagList;
    std::vector<std::string> m_genres;
};

} // soundcloud

#endif // QUERY_H
