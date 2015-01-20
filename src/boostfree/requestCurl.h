#include <curl/curl.h>
#include <cstdint>
#include <string>

namespace soundcloud {

class requestCurl
{
public:
    requestCurl(const std::string& url);
    requestCurl();
    ~requestCurl();

    void setURL(const std::string& url);
    std::string getURL() {
        return m_url;
    }

    void perform();
    std::string getResponse();

private:
    std::string m_url;
    CURL *m_curlHandle;

    static void initializeIfNeeded();
    static void deinitIfNeeded();
    static bool s_initialized;
    static uint32_t s_objectCount;

};

} // namespace soundcloud
