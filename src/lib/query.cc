#include "query.h"
#include <cassert>

namespace soundcloud {

void appendParamListToString(std::string& rQString, const std::string& paramName, const std::vector<std::string>& list)
{
    if (list.size()) {
        rQString.append(paramName);
        for (size_t i = 0; i < list.size(); ++i) {
            rQString.append(list[i]);
            if (i != (list.size()-1)) {
                rQString.append(",");
            }
        }
    }
}

// TODO: move code into ctr
std::string TracksQuery::getURLString() const
{
    assert(!m_baseURL.empty());
    assert(!m_clientID.empty());
    assert(m_limit);
    std::string urlString = m_baseURL + "/tracks?client_id=" + m_clientID +"&limit="+ std::to_string(m_limit) + "&linked_partitioning=1";
    // if limit
    appendParamListToString(urlString, "&tags=", m_tagList);
    appendParamListToString(urlString, "&genres=", m_genres);
    return urlString;
}



} // soundcloud


