#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <iostream>

#include "user.h"

namespace soundcloud {

class Track
{
public:
    Track(
        const std::string& title,
        const std::string& description,
        const std::string& genre,
        const unsigned& duration,
        const std::string& stream_url,
        const std::string& license,
        const std::string& artwork_url,
        const std::string& waveform_url,
        const User& user)
        : m_title(title)
        , m_description(description)
        , m_genre(genre)
        , m_duration(duration)
        , m_stream_url(stream_url)
        , m_license(license)
        , m_artwork_url(artwork_url)
        , m_waveform_url(waveform_url)
        , m_user(user)
    {
    }

    ~Track() {}

    const std::string& title() const {
        return m_title;
    }

    const char* c_title() const {
        return m_title.c_str();
    }

    const std::string& description() const {
        return m_description;
    }

    const char* c_description() const {
        return m_description.c_str();
    }

    const std::string& genre() const {
        return m_genre;
    }

    const char* c_genre() const {
        return m_genre.c_str();
    }

    const unsigned duration() const {
        return m_duration;
    }

    const std::string& stream_url() const {
        return m_stream_url;
    }

    const char* c_stream_url() const {
        return m_stream_url.c_str();
    }

    const std::string& license() const {
        return m_license;
    }

    const std::string& artwork_url() const {
        return m_artwork_url;
    }

    const char* c_artwork_url() const {
        return m_artwork_url.c_str();
    }

    const std::string& waveform_url() const {
        return m_waveform_url;
    }

    const User& user() const {
        return m_user;
    }

    const char* c_userName() const {
        return m_user.username().c_str();
    }


private:
    std::string m_title;
    std::string m_description;
    std::string m_genre;
    unsigned m_duration;
    std::string m_stream_url;
    std::string m_license;
    std::string m_artwork_url;
    std::string m_waveform_url;
    User m_user;
};

inline std::ostream& operator<<(std::ostream& os, const Track& track)
{
    os  << "Track =>" << std::endl
        << "\ttitle: " << track.title() << std::endl
        << "\tdescription: " << track.description() << std::endl
        << "\tgenre: " << track.genre() << std::endl
        << "\tduration: " << track.duration() << std::endl
        << "\tstream_url: " << track.stream_url() << std::endl
        << "\tlicense: " << track.license() << std::endl
        << "\tartwork_url: " << track.artwork_url() << std::endl
        << "\twaveform_url: " << track.waveform_url() << std::endl
        << "\tuser: " << track.user() << std::endl;
  return os;
}


}  // soundcloud


#endif // TRACK_H
