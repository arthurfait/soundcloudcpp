#include "requestCurl.h"
#include <cassert>

namespace soundcloud {

// FIXME: proccess all error cases

static int writeCallback(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;

    if (buffer != NULL) {
        // valide for strings only?
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

requestCurl::requestCurl(const std::string& url)
    : m_url(url)
{
    initializeIfNeeded();
    setupCurlHandle();
    if (m_curlHandle && !url.empty()) {
        curl_easy_setopt(m_curlHandle, CURLOPT_URL, url.c_str());
    }

    s_objectCount++;
}

requestCurl::requestCurl()
{
    initializeIfNeeded();
    setupCurlHandle();
    s_objectCount++;
}

requestCurl::~requestCurl()
{
    if (m_curlHandle) {
        curl_easy_cleanup(m_curlHandle);
        m_curlHandle = nullptr;
    }
    // TODO: this part is about ot think
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

void requestCurl::setSSLOptions(const SSLOps& ops)
{
    assert(m_curlHandle);
    if (ops.skip_peer_verification) {
        curl_easy_setopt(m_curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
    }

    if (ops.skip_hostname_verification) {
        curl_easy_setopt(m_curlHandle, CURLOPT_SSL_VERIFYHOST, 0L);
    }
}

bool requestCurl::perform()
{
    bool success = false;
    if (m_curlHandle) {
        CURLcode res;
        m_stringData.clear();
        res = curl_easy_perform(m_curlHandle);
        if (res == CURLE_OK) {
            success = true;
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

    }
    return success;
}

std::string requestCurl::getResponse()
{
    return m_stringData;
}

void requestCurl::setupCurlHandle()
{
    m_curlHandle = curl_easy_init();
    if (m_curlHandle) {
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, &m_stringData);
    }
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
