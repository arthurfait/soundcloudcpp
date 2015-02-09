#include "query.h"

namespace soundcloud {

std::string TracksQuery::getURLString() const
{
    return m_baseURL + "/tracks?client_id="+m_clientID+"&limit=10&tag="+m_tag;
}

} // soundcloud


