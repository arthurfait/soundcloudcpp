#include <curl/curl.h>
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
    static bool s_initialized;

};

} // namespace soundcloud
