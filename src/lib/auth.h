/*
 * @file            auth.h
 * @author          Arthur Fait
 * @date            23.05.14
 */

#include <string>

namespace soundcloud {

class AuthDelegate {
public:
    explicit AuthDelegate(const std::string& client_id);
    std::string getAuthUrl();

private:
    std::string m_clientId;
};

} // soundcloud
