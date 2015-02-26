#include "query.h"
#include <cassert>

namespace soundcloud {

// TODO: move code into ctr
std::string TracksQuery::getURLString() const
{
    assert(!m_baseURL.empty());
    assert(!m_clientID.empty());
    assert(m_limit);
    std::string urlString = m_baseURL + "/tracks?client_id=" + m_clientID +"&limit="+ std::to_string(m_limit) + "&linked_partitioning=1";
    // if limit
    if (m_tagList.size()) {
        urlString.append("&tag=");
        for (size_t i = 0; i < m_tagList.size(); ++i) {
            urlString.append(m_tagList[i]);
            if (i != (m_tagList.size()-1)) {
                urlString.append(",");
            }
        }
    }
    return urlString;
}



} // soundcloud


