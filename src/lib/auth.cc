/*
 * @file            auth.cc
 * @author          Arthur Fait
 * @date            23.05.14
 */


#include "auth.h"
#include <network/requestCurl.h>
#include <cstdio>
namespace soundcloud {

AuthDelegate::AuthDelegate(const std::string& client_id)
    : m_clientId(client_id)
{
}

std::string AuthDelegate::getAuthUrl()
{

    const std::string url = "https://soundcloud.com/connect?client_id="+m_clientId+
    "&rediruri=https://developers.soundcloud.com/callback.html"+
    "&response_type=code"+
    "&scope=non-expiring";

    // printf("%s\n", url.c_str());
    return url;
}


} // soundcloud
