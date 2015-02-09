#include <curl/curl.h>
#include <cstdint>
#include <string>

namespace soundcloud {

class requestCurl
{
public:
    struct SSLOps {
        bool skip_peer_verification = false;
        bool skip_hostname_verification = false;
    };
public:
    requestCurl(const std::string& url);
    requestCurl();
    ~requestCurl();

    void setURL(const std::string& url);
    std::string getURL() {
        return m_url;
    }

    void setSSLOptions(const SSLOps& ops);

    void perform();
    std::string getResponse();

private:
    void setupCurlHandle();

private:
    std::string m_url;
    CURL *m_curlHandle;
    std::string m_stringData;


    static void initializeIfNeeded();
    static void deinitIfNeeded();
    static bool s_initialized;
    static uint32_t s_objectCount;

};

} // namespace soundcloud
