/*
 * @file         soundcloud_widget.cc
 * @author       Arthur Fait
 * @date         31.08.15
 *
 */
#include "soundcloud_widget.h"
// #include <stdlib.h>
#include <string.h>



#define AUD_PLUGIN_GLIB_ONLY
#include <libaudcore/audstrings.h>
#include <libaudcore/hook.h>
#include <libaudcore/i18n.h>
#include <libaudcore/playlist.h>
#include <libaudcore/plugin.h>
#include <libaudcore/mainloop.h>
// #include <libaudcore/multihash.h>
#include <libaudcore/runtime.h>
#include <libaudgui/libaudgui-gtk.h>
#include <libaudgui/list.h>
#include <libaudgui/menu.h>


class SoundCloudPlugin : public GeneralPlugin
{
public:
    static constexpr PluginInfo info = {
        N_("SoundCloud"),
        "SoundCloud"
    };

    constexpr SoundCloudPlugin () : GeneralPlugin (info, false) {}

    void * get_gtk_widget ();
    int take_message (const char * code, const void * data, int size);
private:
    SoundCloudWidget* sCWidget = nullptr;
};


void * SoundCloudPlugin::get_gtk_widget ()
{
    GtkWidget *frame = nullptr; //= gtk_frame_new(0);
    if (!sCWidget) {
        sCWidget = new SoundCloudWidget();
        frame = gtk_frame_new(0);
        gtk_frame_set_shadow_type((GtkFrame*)frame, GTK_SHADOW_NONE);
        gtk_container_add((GtkContainer*)frame, sCWidget->content());
        // return frame;
    }
    return frame;
}

int SoundCloudPlugin::take_message (const char * code, const void * data, int size)
{
    if (! strcmp (code, "grab focus"))
    {
        // if (entry)
        //     gtk_widget_grab_focus (entry);
        return 0;
    }

    return -1;
}

SoundCloudPlugin aud_plugin_instance;


static void entry_cb (GtkEntry *entry, void *data)
{
    (void)entry;
    SoundCloudWidget* that = reinterpret_cast<SoundCloudWidget*>(data);
    if (that)
        that->OnEntryChanged();
}


static gboolean connect_timeoutCB(gpointer data)
{
    SoundCloudWidget* that = reinterpret_cast<SoundCloudWidget*>(data);
    if (that)
        that->OnConnect();
    return FALSE;
}

static void page_nextButtonCB(GtkWidget *widget, gpointer data)
{
    SoundCloudWidget* that = reinterpret_cast<SoundCloudWidget*>(data);
    if (that)
        that->nextPage();
}

static void activate_cb (GtkTreeView * tree,
                         GtkTreePath * path,
                         GtkTreeViewColumn * col, SoundCloudWidget * that) {
    int row = gtk_tree_path_get_indices (path)[0];
    // std::cout << "clicked: " << row << "\n";
    that->OnActivate(row);
}

void SoundCloudWidget::OnEntryChanged()
{
    const char* searchCString = gtk_entry_get_text ((GtkEntry*)entry);
    if (searchCString && strlen(searchCString)) {
        if (m_searchTimer) {
            g_source_remove(m_searchTimer);
        }
        m_searchString.assign(searchCString);
        m_searchTimer = g_timeout_add(500, connect_timeoutCB, this);
    }
}

void SoundCloudWidget::OnActivate(int index)
{
    auto url = m_client.resolveTrackStream(m_currentTrackList[index]);
    // std::cout << "url: " << url << "\n";
    // std::cout << "num: " << aud_playlist_get_active() << "\n";
    // Index * filenames = index_new ();
    // Index * tuples = index_new ();
    // // for (int m = 0; m < item->matches->len; m ++) {
    //     index_insert (filenames, -1, str_to_utf8(url.c_str(), url.size()));
    //     Tuple* tup = tuple_new();
    //
    //     char *artist =  str_to_utf8(m_currentTrackList[index].c_userName(), m_currentTrackList[index].user().username().size());
    //     tuple_set_str(tup, FIELD_ARTIST, artist);
    //     str_unref(artist);
    //
    //     char *title = str_to_utf8(m_currentTrackList[index].c_title(), m_currentTrackList[index].title().size());
    //     tuple_set_str(tup, FIELD_TITLE, title);
    //     str_unref(title);
    //
    //     char *genre = str_to_utf8(m_currentTrackList[index].c_genre(), m_currentTrackList[index].genre().size());
    //     tuple_set_str(tup, FIELD_GENRE, genre);
    //     str_unref(genre);
    //
    //     // tuple_set_str(tup, FIELD_COMMENT, str_to_utf8(m_currentTrackList[index].c_description(), m_currentTrackList[index].description().size()));
    //     tuple_set_int(tup, FIELD_LENGTH, m_currentTrackList[index].duration());
    //
    //     index_insert (tuples, -1, tup);
    // }
    // aud_playlist_entry_insert_batch (aud_playlist_get_active (), -1, filenames,
    //  tuples, 0);
    Tuple tuple;
    tuple.set_str(Tuple::field_by_name("title"), m_currentTrackList[index].c_title());
    tuple.set_str(Tuple::field_by_name("artist"), m_currentTrackList[index].c_userName());
    tuple.set_str(Tuple::field_by_name("genre"), m_currentTrackList[index].c_genre());

    auto playlist = Playlist::active_playlist();
    playlist.insert_entry(-1, url.c_str(), std::move(tuple), false);

    // aud_playlist_entry_insert (aud_playlist_get_active (), -1 , url.c_str(), std::move(tuple), 0);
}


void SoundCloudWidget::fillPQList(const std::vector<soundcloud::Track>& tracks)
{
    gtk_list_store_clear(playQueuestore);
    GtkTreeIter iter;
    m_currentTrackList = tracks;
    for (auto &track: tracks) {
        gtk_list_store_append (playQueuestore, &iter);
        gtk_list_store_set (playQueuestore, &iter,
                          TITLE_COLUMN, track.title().c_str(),
                          ALBUM_COLUMN, track.genre().c_str(),
                          ARTIST_COLUMN, track.user().username().c_str(),
                          -1);
    }
}

const std::string kClientID = "a5a98f5d549a83896d565f69eb644b65";

SoundCloudWidget::SoundCloudWidget()
    : m_client(kClientID)
{
    createContent();
}


void SoundCloudWidget::createContent()
{
    // prevButton = gtk_button_new_with_label("prev");
    // g_signal_connect(prevButton, "clicked", G_CALLBACK(prev_callback),(gpointer) this);

    entry = gtk_entry_new ();
    gtk_entry_set_icon_from_icon_name ((GtkEntry *) entry, GTK_ENTRY_ICON_PRIMARY, "edit-find");
    // onlu 3.0 FIXME: add ifdef here
    // gtk_entry_set_placeholder_text ((GtkEntry *) entry, "Search SoundCloud");
    gtk_entry_set_text((GtkEntry *) entry, m_searchString.c_str());
    g_signal_connect (entry, "destroy", (GCallback) gtk_widget_destroyed, & entry);
    g_signal_connect (entry, "changed", (GCallback) entry_cb, (gpointer)this);
    // g_signal_connect (entry, "activate", (GCallback) action_play, (gpointer)this);

    page_nextButton = gtk_button_new_with_label("show next 30 tracks");
    g_signal_connect(page_nextButton, "clicked", G_CALLBACK(page_nextButtonCB),(gpointer) this);


    // box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    box = gtk_hbox_new (0, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
//    gtk_box_pack_start (GTK_BOX (box), connectButton, FALSE, FALSE, 3);
    gtk_box_pack_start ((GtkBox *) box, entry, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box), page_nextButton, FALSE, FALSE, 3);

//    gtk_widget_show(connectButton);

    gtk_widget_show(page_nextButton);


    playQueuestore = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    pqTree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(playQueuestore));
//    gtk_tree_view_set_fixed_height_mode ((GtkTreeView *) pqTree, true);
//    gtk_tree_view_set_vadjustment((GtkTreeView*) pqTree, GTK_ADJUSTMENT(gtk_adjustment_new(0,0,100,1,10,100)));
    pqTreeScrollWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pqTreeScrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Track",
                                                   renderer,
                                                   "text", TITLE_COLUMN,
                                                   nullptr);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Genre",
                                                   renderer,
                                                   "text", ALBUM_COLUMN,
                                                   nullptr);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    renderer = gtk_cell_renderer_text_new ();
    // g_object_set (renderer, "mode", GTK_CELL_RENDERER_MODE_ACTIVATABLE, NULL);
    column = gtk_tree_view_column_new_with_attributes ("Added by",
                                                   renderer,
                                                   "text", ARTIST_COLUMN,
                                                   nullptr);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    g_signal_connect (pqTree, "row-activated", (GCallback) activate_cb, this);

    gtk_container_add(GTK_CONTAINER(pqTreeScrollWindow), pqTree);
    gtk_widget_show(pqTree);


    // vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    vbox = gtk_vbox_new (0, 0);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 2);

    gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (vbox), pqTreeScrollWindow, true, true, 3);

    gtk_widget_show(box);
    gtk_widget_show(pqTreeScrollWindow);

    gtk_widget_show(vbox);

    m_searchTimer = g_timeout_add(500, connect_timeoutCB, this);
}

void SoundCloudWidget::OnConnect()
{
    m_searchTimer = 0;
    std::vector<std::string> taglist = {};
    std::vector<std::string> genres = {};

    std::string query = "";
    if (m_searchString[0] == '@') {
        genres.push_back(m_searchString.substr(1));
    } else if (m_searchString[0] == '#') {
        taglist.push_back(m_searchString.substr(1));
    } else {
        query = m_searchString.substr(1);
    }

    m_currentRequest = m_client.getTracks(query, taglist, genres, 30);
    auto tracks = m_currentRequest->next();
    fillPQList(tracks);
}

void SoundCloudWidget::nextPage()
{
    auto tracks = m_currentRequest->next();
    fillPQList(tracks);
}
