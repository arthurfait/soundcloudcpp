/*
 * @file            player.h
 * @author       Arthur Fait
 * @date          23.05.14
 */


#ifndef PLAYER_H
#define PLAYER_H


#include <gst/gst.h>
#include <glib.h>



#endif // PLAYER_H
gst-launch -v videotestsrc ! video/x-raw-yuv ! mfw_v4lsink device=/dev/video18 axis-left=0 axis-top=0 disp-width=800 disp-height=480
