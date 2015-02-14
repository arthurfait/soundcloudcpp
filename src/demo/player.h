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

    enum State {
        eStatePlaying,
        eStatePaused,
        eStateStopped,
        eStateEos,
        eStateError
    };

    Player(PlayerPlaybackMode mode = ePlayerPlaybackNormal);
    ~Player();

    void setStateChangeCallback(std::function<void(State)> callback) {
        m_state_callback = callback;
    }

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

    std::function<void(State)> m_state_callback;

    PlayerPlaybackMode m_mode;
    GstElement *playbin2;
    GstElement* videosink;

    bool m_paused;
    float m_duration;
};


} // demo

#endif // PLAYER_H

