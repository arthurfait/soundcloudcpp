#include "requestCurl.h"

namespace soundcloud {

// FIXME: proccess all error cases

requestCurl::requestCurl(const std::string& url)
    : m_url(url)
{
    initializeIfNeeded();
    m_curlHandle = curl_easy_init();
    if (m_curlHandle && !url.empty()) {
        curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
    }
    s_objectCount++;
}

requestCurl::requestCurl()
{
    initializeIfNeeded();
    m_curlHandle = curl_easy_init();
    s_objectCount++;
}

requestCurl::~requestCurl()
{
    if (m_curlHandle) {
        curl_easy_cleanup(m_curlHandle);
        m_curlHandle = nullptr;
    }
    if (--s_objectCount == 0) {
        curl_global_cleanup();
        s_initialized = false;
    }
}

void requestCurl::setURL(const std::string& url)
{
    if (m_curlHandle && !url.empty()) {
        curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
    }
}

void requestCurl::perform()
{
    if (m_curlHandle) {
        CURLcode res;
        res = curl_easy_perform(m_curlHandle);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
}

std::string requestCurl::getResponse()
{
    return "";
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
uint32_t requestCurl::s_objectCount = 0;


} // namespace soundcloud
