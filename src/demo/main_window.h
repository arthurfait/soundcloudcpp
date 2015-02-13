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

class MainWindow
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

// for testing
    void fillPQList(std::vector<PQItem>& items);


    void OnConnect();


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

    // cached
    uint32_t m_cachedDuration;
    uint32_t m_cachedPosition;

    // UI
    // control
    GtkWidget *window;
    GtkWidget *connectButton;
    GtkWidget *playButton;
    GtkWidget *pauseButton;
    GtkWidget *stopButton;
    GtkWidget *nextButton;
    GtkWidget *prevButton;
    GtkWidget *box;
    GtkWidget *progress;

    // playQueue box
    GtkListStore *playQueuestore;
    GtkWidget   *pqTree;
    GtkWidget   *pqTreeScrollWindow;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    GtkWidget *vbox;



};






#endif // MAIN_WINDOW_H

