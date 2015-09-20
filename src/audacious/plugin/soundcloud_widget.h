/*
 * @file         soundcloud_widget.h
 * @author       Arthur Fait
 * @date         31.08.15
 *
 */

#ifndef SOUNDCLOUD_WIDGET_H
#define SOUNDCLOUD_WIDGET_H

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <client.h>

class SoundCloudWidget
{
public:
    // struct PQItem {
    //     std::string title;
    //     std::string album;
    //     std::string artist;
    // };
public:
    SoundCloudWidget();
    virtual ~SoundCloudWidget() {}

    void createContent();

    // void show();
    void OnActivate(int index);
    void OnConnect();

    void nextPage();

    GtkWidget* content() {
        return vbox;
    }

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
    std::vector<soundcloud::Track> m_currentTrackList;

    // UI
    GtkWidget *entry;
    GtkWidget *page_nextButton;
    GtkWidget *box;

    // playQueue box
    GtkListStore *playQueuestore;
    GtkWidget   *pqTree;
    GtkWidget   *pqTreeScrollWindow;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    GtkWidget *vbox;
};

#endif // SOUNDCLOUD_WIDGET_H
