 /*
  * @file            player.cpp
  * @author       Arthur Fait
  * @date          29.09.2014
  */


#include <cmath>
#include <limits>
#include "player.h"
#include "log.h"


namespace demo {

static void error_cb(GstBus *, GstMessage *msg, Player *player);
static void eos_cb(GstBus *, GstMessage *msg, Player *player);
static void state_changed_cb(GstBus *, GstMessage *msg, Player *player);

typedef enum {
  GST_PLAY_FLAG_VIS           = (1 << 3) /* Enable rendering of visualizations when there is no video stream. */
} GstPlayFlags;

Player::Player(PlayerPlaybackMode mode)
    : m_mode(mode)
    , m_paused(true)
    , m_duration(0.0)
{
    initializeGStreamer();
    playbin2 = gst_element_factory_make ("playbin2", "playbin2");
    if (!playbin2) {
        g_printerr ("Not all elements could be created.\n");
        return;
    }

    if (m_mode == ePlayerPlaybackNormal) {
    // create videosink by hand
        videosink = gst_element_factory_make("dri2videosink",NULL);
        if (videosink) {
            log_info("%s || using dri2videosink",__PRETTY_FUNCTION__);
            g_object_set(playbin2, "video-sink", videosink, NULL);
        } else {
            videosink = gst_element_factory_make("ximagesink", NULL);
            if (videosink) {
                log_info("%s || using ximagesink",__PRETTY_FUNCTION__);
                g_object_set(videosink, "force-aspect-ratio", TRUE, NULL);
                g_object_set(playbin2, "video-sink", videosink, NULL);
            } else {
                gst_object_unref(playbin2);
                return;
            }
        }
        // install visualization
        // guint flags;
        // g_object_get (playbin2, "flags", &flags, NULL);
        // flags |= GST_PLAY_FLAG_VIS;
        // g_object_set (playbin2, "flags", flags, NULL);

        // GstElement* vis_plugin = gst_element_factory_make ("goom2k1", "vis_goom");
        // g_object_set(playbin2, "vis-plugin", vis_plugin, NULL);
    } else if (m_mode == ePlayerPlaybackVis) {
        videosink = gst_element_factory_make("ximagesink", NULL);
        if (videosink) {
            log_info("%s || using ximagesink",__PRETTY_FUNCTION__);
            g_object_set(videosink, "force-aspect-ratio", TRUE, NULL);
            g_object_set(playbin2, "video-sink", videosink, NULL);
            // install visualization
            guint flags;
            g_object_get (playbin2, "flags", &flags, NULL);
            flags |= GST_PLAY_FLAG_VIS;
            g_object_set (playbin2, "flags", flags, NULL);

            GstElement* vis_plugin = gst_element_factory_make ("goom2k1", "vis_goom");
            g_object_set(playbin2, "vis-plugin", vis_plugin, NULL);
        }
    } else {
        videosink = gst_element_factory_make("fakesink",NULL);
        g_object_set(playbin2, "video-sink", videosink, NULL);
    }

    GstBus *bus;
    // Instruct the bus to emit signals for each received message, and connect to the interesting signals
    bus = gst_element_get_bus (playbin2);
    gst_bus_add_signal_watch (bus);
    g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)error_cb, this);
    g_signal_connect (G_OBJECT (bus), "message::eos", (GCallback)eos_cb, this);
    g_signal_connect (G_OBJECT (bus), "message::state-changed", (GCallback)state_changed_cb, this);

   gst_object_unref (bus);

//   gst_object_unref(vis_plugin);
}

Player::~Player()
{
    if (!playbin2)
        gst_object_unref (playbin2);
}

void Player::load(const std::string& path)
{
    gchar* uri = g_filename_to_uri(path.c_str(), NULL, NULL);
//  gst_uri_is_valid()
    stop(); // I dont know but this should work
    g_object_set(playbin2, "uri", uri, NULL);
    g_free(uri);
}

void Player::play()
{
    GstStateChangeReturn ret;
    /* Start playing */
    ret = gst_element_set_state (playbin2, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
//        gst_object_unref (playbin2);
    //    throw
    }
}

void Player::pause()
{
    GstStateChangeReturn ret;
    /* Start playing */
    ret = gst_element_set_state (playbin2, GST_STATE_PAUSED);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
    }
    m_paused = true;
}

void Player::stop()
{
    GstStateChangeReturn ret;
    /* Start playing */
    ret = gst_element_set_state (playbin2, GST_STATE_READY);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
     //    throw
    }
}

/*static*/
bool Player::gstInitialized = false;

void Player::seek(float newPosition)
{
    // Avoid useless seeking.
    if (!playbin2)
        return;


    double seconds;
    double microSeconds = modf(newPosition, &seconds) * 1000000;
    GTimeVal timeValue;
    timeValue.tv_sec = static_cast<glong>(seconds);
    timeValue.tv_usec = static_cast<glong>(roundf(microSeconds / 10000) * 10000);

    GstClockTime clockTime = GST_TIMEVAL_TO_TIME(timeValue);
    log_info("Seek: %" GST_TIME_FORMAT, GST_TIME_ARGS(clockTime));

    if (!gst_element_seek(playbin2, 1.0,
            GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
            GST_SEEK_TYPE_SET, clockTime,
            GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE))
        log_warning("Seek to %f failed", newPosition);
    else {
//        m_seeking = true;
//        m_seekTime = newPosition;
    }
}

double Player::getPosition()
{
    // Position is only available if no async state change is going on and the state is either paused or playing.
    gint64 position = GST_CLOCK_TIME_NONE;
    GstQuery* query= gst_query_new_position(GST_FORMAT_TIME);
    if (gst_element_query(playbin2, query))
        gst_query_parse_position(query, 0, &position);

    float result = 0.0f;
    if (static_cast<GstClockTime>(position) != GST_CLOCK_TIME_NONE)
        result = static_cast<double>(position) / GST_SECOND;

    gst_query_unref(query);

    return result;
}

double Player::getDuration()
{
    if (!playbin2)
        return 0.0f;

    GstFormat timeFormat = GST_FORMAT_TIME;
    gint64 timeLength = 0;

    bool failure = !gst_element_query_duration(playbin2, &timeFormat, &timeLength) || timeFormat != GST_FORMAT_TIME || static_cast<guint64>(timeLength) == GST_CLOCK_TIME_NONE;
    if (failure) {
         log_warning("Time duration query failed for");
         return std::numeric_limits<float>::infinity();
    }

    return static_cast<double>(timeLength) / GST_SECOND;
}

uint8_t Player::getVolume()
{
    gdouble fVolume = 0.0;
    g_object_get(playbin2, "volume", &fVolume, NULL);
    return static_cast<uint8_t>(fVolume*100.0);
}

void Player::setVolume(uint8_t newVol)
{
    if (newVol>100)
        newVol = 100;
    gdouble fVolume = static_cast<float>(newVol)/100.0;
    g_object_set(playbin2, "volume", fVolume, NULL);
}

void Player::handleEos()
{
    m_paused = true;
    m_state_callback(eStateEos);
}

void Player::handleError()
{
    m_state_callback(eStateError);
}

void Player::handleStateCnanged(GstMessage *msg)
{
    if (GST_MESSAGE_SRC(msg) == reinterpret_cast<GstObject*>(playbin2)) {
        GstState state;
        GstState pending;
        GstStateChangeReturn ret = gst_element_get_state(playbin2,
                &state, &pending, 250 * GST_NSECOND);
        if (ret == GST_STATE_CHANGE_SUCCESS) {
            log_info("State: %s, pending: %s",
                gst_element_state_get_name(state),
                gst_element_state_get_name(pending));
            if (state == GST_STATE_PLAYING) {
                if (m_paused) {
                    m_paused = false;
                    m_state_callback(eStatePlaying);
                }
            } else if (state == GST_STATE_PAUSED ) {
                if (m_paused) {
                    m_paused = true;
                    m_state_callback(eStatePaused);
                }
            } else {
                m_paused = true;
                m_state_callback(eStatePaused);

            }

        }
    }

}

/**
 * @brief initialize gstreamer Framework,
 * plugins are readed at this point
  * @return
 */
bool Player::initializeGStreamer()
{
    GError* error = 0;
    // FIXME: We should probably pass the arguments from the command line.
    gstInitialized = gst_init_check(0, 0, &error);
    if (error)
        g_free(error);
    return gstInitialized;
}

static void error_cb (GstBus *bus, GstMessage *msg, Player *player)
{
    GError *err;
    gchar *debug_info;
    // Print error details on the screen
    gst_message_parse_error (msg, &err, &debug_info);
    g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
    g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
    g_clear_error (&err);
    g_free (debug_info);

    player->handleError();
}

    /* This function is called when an End-Of-Stream message is posted on the bus.
    * We just set the pipeline to READY (which stops playback) */
static void eos_cb (GstBus *bus, GstMessage *msg, Player *player)
{
    g_print ("End-Of-Stream reached.\n");
    player->handleEos();
}

static void state_changed_cb(GstBus*, GstMessage *msg, Player *player)
{
    player->handleStateCnanged(msg);
}

} // demo
