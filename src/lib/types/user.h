#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

namespace soundcloud {

class User
{
public:
    User(
        const std::string& username,
        const std::string& permalink_url,
        const std::string& avatar_url,
        const std::string& uri,
        const uint64_t& id)
        : m_username(username)
        , m_permalink_url(permalink_url)
        , m_avatar_url(avatar_url)
        , m_uri(uri)
        , m_id(id)
    {
    }

    ~User() {}

    const std::string& username() const {
            return m_username;
    }
    const std::string& permalink_url() const {
            return m_permalink_url;
    }
    const std::string& avatar_url() const {
            return m_avatar_url;
    }
    const std::string& uri() const {
            return m_uri;
    }
    const uint64_t& id() const {
            return m_id;
    }

private:
    std::string m_username;
    std::string m_permalink_url;
    std::string m_avatar_url;
    std::string m_uri;
    uint64_t m_id;
};



inline std::ostream& operator<<(std::ostream& os, const User& user)
{
    os  << "User =>" << std::endl
        << "\tusername: " << user.username() << std::endl
        << "\tpermalink_url: " << user.permalink_url() << std::endl
        << "\tavatar_url: " << user.avatar_url() << std::endl
        << "\turi: " << user.uri() << std::endl
        << "\tid: " << user.id() << std::endl;
  return os;
}


}  // soundcloud


#endif // USER_H
