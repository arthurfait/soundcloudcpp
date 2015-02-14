/*
 * @file            player.h
 * @author       Arthur Fait
 * @date          23.05.14
 */

#ifndef PLAYER_H
#define PLAYER_H

// #include <X11/Xlib.h>
#include <gst/gst.h>
// #include <gst/interfaces/xoverlay.h>
#include <string>
#include <functional>
// #include "log.hpp"

namespace demo {

class Player{
public:
    enum PlayerPlaybackMode {
        ePlayerPlaybackBackground,
        ePlayerPlaybackVis,
        ePlayerPlaybackNormal
    };

public:
    class IPlayerObserver {
    public:
        virtual void onPlaying()  = 0;
        virtual void onPaused()  = 0;
        virtual void onStopped()  = 0;
        virtual void onEos()  = 0;
        virtual void onError(PlayerTypes::PlaybackErrorCode errorCode)  = 0;


        virtual void onSeekStart() = 0;
        virtual void onSeekDone() = 0;

        virtual void onPositionUpdate(float position)  = 0;

public:
    // virtual destructor for interface
    virtual ~PlayerObserver() {}
};


    Player(PlayerPlaybackMode mode = ePlayerPlaybackNormal);
    ~Player();


    void load(const std::string& path);
    void play();
    void pause();
    void stop();

    void seek(float newPosition);

    bool paused() {
        return m_paused;
    }

    double getPosition();
    double getDuration();

    uint8_t getVolume();
    void setVolume(uint8_t newVol);

    // void setX11Id(Window wind);


    void handleStateCnanged(GstMessage *msg);
    void handleEos();
    void handleError();
private:

    static bool initializeGStreamer();
    static bool gstInitialized;

    std::set<IPlayerObserver*> m_observers;

    PlayerPlaybackMode m_mode;
    GstElement *playbin2;
    GstElement* videosink;

    bool m_paused;
    float m_duration;
};


} // demo

#endif // PLAYER_H

