/*
 * @file            MainWindow.h
 * @author       Arthur Fait
 * @date          23.05.14
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <client.h>
#include "player.h"

class MainWindow: public demo::Player::IPlayerObserver
{
public:
    struct PQItem {
        std::string title;
        std::string album;
        std::string artist;
    };
public:
    MainWindow();
    virtual ~MainWindow() {}
    void createWindow();
    void createContent();
    void show();

    void updateProgress();
    void handleUpdateTimer();

    void OnActivate(int index);


// button handlers
    void OnPlay();
    void OnPause();
    void OnStop();
    void OnPrev();
    void OnNext();
    void OnVolume(gdouble volume);

// for testing
    void fillPQList(std::vector<PQItem>& items);


    void OnConnect();
    void nextPage();

    virtual void onPlaying()  override;
    virtual void onPaused()  override;
    virtual void onStopped()  override;
    virtual void onEos()  override;
    virtual void onError(int errorCode)  override;
    virtual void onSeekStart() override;
    virtual void onSeekDone() override;

private:
    enum {
        TITLE_COLUMN,
        ALBUM_COLUMN,
        ARTIST_COLUMN,
        N_COLUMNS
    };

private:
    void fillPQList(const std::vector<soundcloud::Track>& tracks);

private:

    //
    soundcloud::Client m_client;
    std::shared_ptr<soundcloud::TracksRequest> m_currentRequest;

    // cached
    uint32_t m_cachedDuration;
    uint32_t m_cachedPosition;
    std::vector<soundcloud::Track> m_currentTrackList;
    std::uint32_t m_currentTrackIndex;


    //
    guint m_timerHandle;

    // UI
    // control
    GtkWidget *window;
//    GtkWidget *connectButton;
    GtkWidget *playButton;
    GtkWidget *pauseButton;
    GtkWidget *stopButton;
    GtkWidget *nextButton;
    GtkWidget *prevButton;
    GtkWidget *page_nextButton;
    GtkWidget *volumeSlider;
    GtkWidget *box;
    GtkWidget *progress;

    // playQueue box
    GtkListStore *playQueuestore;
    GtkWidget   *pqTree;
    GtkWidget   *pqTreeScrollWindow;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    GtkWidget *vbox;
    demo::Player m_player;
};






#endif // MAIN_WINDOW_H

