#include <curl/curl.h>
#include <string>

namespace soundcloud {

class requestCurl
{
public:
requestCurl::requestCurl(const std::string& url)
    : m_url(url)
{

}

requestCurl::requestCurl()
{

}

requestCurl::~requestCurl()
{

}


void requestCurl::setURL(const std::string& url)
{

}

void requestCurl::perform()
{

}

std::string requestCurl::getResponse()
{

}

// static
void requestCurl::initializeIfNeeded()
{
    if (!s_initialized) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        s_initialized = true;
    }
}

 bool requestCurl::s_initialized = false;

};



} // namespace soundcloud
