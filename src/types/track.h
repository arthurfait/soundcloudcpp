#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <iostream>

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
        const std::string& waveform_url)
        : m_title(title)
        , m_description(description)
        , m_genre(genre)
        , m_duration(duration)
        , m_stream_url(stream_url)
        , m_license(license)
        , m_artwork_url(artwork_url)
        , m_waveform_url(waveform_url)
    {
    }

    ~Track() {}

    const std::string& title() const {
        return m_title;
    }

    const std::string& description() const {
        return m_description;
    }

    const std::string& genre() const {
        return m_genre;
    }

    const unsigned duration() const {
        return m_duration;
    }

    const std::string& stream_url() const {
        return m_stream_url;
    }

    const std::string& license() const {
        return m_license;
    }

    const std::string& artwork_url() const {
        return m_artwork_url;
    }

    const std::string& waveform_url() const {
        return m_waveform_url;
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
};

std::ostream& operator<<(std::ostream& os, const Track& track)
{
    os  << "Track =>" << std::endl
        << "\ttitle: " << track.title() << std::endl
        << "\tdescription: " << track.description() << std::endl
        << "\tgenre: " << track.genre() << std::endl
        << "\tduration: " << track.duration() << std::endl
        << "\tstream_url: " << track.stream_url() << std::endl
        << "\tlicense: " << track.license() << std::endl
        << "\tartwork_url: " << track.artwork_url() << std::endl
        << "\twaveform_url: " << track.waveform_url() << std::endl;
  return os;
}


}  // soundcloud


#endif // TRACK_H
