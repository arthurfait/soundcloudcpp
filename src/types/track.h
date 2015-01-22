#include <string>

namespace soundcloud {

class Track
{
public:
    Track(
        const std::string& title,
        const std::string& description,
        const std::string& genre,
        const std::string& duration,
        const std::string& stream_url,
        const std::string& license,
        const std::string& artwork_url,
        const std::string& waveform_url)
        : std::string m_title(title)
        , std::string m_description(description)
        , std::string m_genre(genre)
        , std::string m_duration(duration)
        , std::string m_stream_url(stream_url)
        , std::string m_license(license)
        , std::string m_artwork_url(artwork_url)
        , std::string m_waveform_url(waveform_url)
    {
    }
    ~Track() {}

private:
    std::string m_title;
    std::string m_description;
    std::string m_genre;
    std::string m_duration;
    std::string m_stream_url;
    std::string m_license;
    std::string m_artwork_url;
    std::string m_waveform_url;
};



}  // soundcloud
