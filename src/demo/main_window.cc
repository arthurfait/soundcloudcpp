/*
  * @file            main_window.cc
 * @author       Arthur Fait
 * @date          23.05.14
 */


#include "main_window.h"
#include <stdlib.h>


void connect_callback(GtkWidget *widget, gpointer data)
{
    MainWindow* that = reinterpret_cast<MainWindow*>(data);
    if (that)
        that->OnConnect();
}

void play_callback(GtkWidget *widget, gpointer data)
{

}

void pause_callback(GtkWidget *widget, gpointer data)
{

}

void stop_callback(GtkWidget *widget, gpointer data)
{

}

void prev_callback(GtkWidget *widget, gpointer data)
{

}

void next_callback(GtkWidget *widget, gpointer data)
{

}

static void activate_cb (GtkTreeView * tree,
                         GtkTreePath * path,
                         GtkTreeViewColumn * col, MainWindow * that) {
     int row = gtk_tree_path_get_indices (path)[0];
     std::cout << "cliecked: " << row << "\n";
    that->OnActivate(row);

}

void MainWindow::OnActivate(int index)
{
    std::cout << "cliecked " << index << "\n" << m_currentTrackList[index].title() << "\n";
    std::cout << "url: " << m_client.resolveTrackStream(m_currentTrackList[index]) << "\n";
    m_player.load(m_client.resolveTrackStream(m_currentTrackList[index]));
    m_player.play();
}

// for testing
void MainWindow::fillPQList(std::vector<PQItem>& items)
{
    GtkTreeIter iter;
    for (auto &item: items) {
        gtk_list_store_append (playQueuestore, &iter);
        gtk_list_store_set (playQueuestore, &iter,
                          TITLE_COLUMN, item.title.c_str(),
                          ALBUM_COLUMN, item.album.c_str(),
                          ARTIST_COLUMN, item.artist.c_str(),
                          -1);
    }
}

void MainWindow::fillPQList(const std::vector<soundcloud::Track>& tracks)
{
    GtkTreeIter iter;
    m_currentTrackList = tracks;
    for (auto &track: tracks) {
        gtk_list_store_append (playQueuestore, &iter);
        gtk_list_store_set (playQueuestore, &iter,
                          TITLE_COLUMN, track.title().c_str(),
                          ALBUM_COLUMN, track.genre().c_str(),
                          ARTIST_COLUMN, track.stream_url().c_str(),
                          -1);
    }
}

const std::string kClientID = "a5a98f5d549a83896d565f69eb644b65";

MainWindow::MainWindow()
    : m_client(kClientID)
    , m_player(demo::Player::ePlayerPlaybackBackground)
{
    createWindow();
    createContent();
}

void MainWindow::createWindow()
{
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Pixmap'd Buttons!");

    /* It's a good idea to do this for all windows. */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
}

void MainWindow::createContent()
{
    connectButton = gtk_toggle_button_new_with_label("connect");
    gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON(connectButton), TRUE);
    g_signal_connect(connectButton, "toggled", G_CALLBACK(connect_callback),(gpointer) this);

    playButton = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);
    g_signal_connect(playButton, "clicked", G_CALLBACK(play_callback),(gpointer) nullptr);

    pauseButton = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PAUSE);
    g_signal_connect(pauseButton, "clicked", G_CALLBACK(pause_callback),(gpointer) nullptr);

    stopButton = gtk_button_new_from_stock(GTK_STOCK_MEDIA_STOP);
    g_signal_connect(stopButton, "clicked", G_CALLBACK(stop_callback),(gpointer) nullptr);

    nextButton = gtk_button_new_from_stock(GTK_STOCK_MEDIA_NEXT);
    g_signal_connect(nextButton, "clicked", G_CALLBACK(next_callback),(gpointer) nullptr);

    prevButton = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PREVIOUS);
    g_signal_connect(prevButton, "clicked", G_CALLBACK(prev_callback),(gpointer) nullptr);

    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    gtk_box_pack_start (GTK_BOX (box), connectButton, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), playButton, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), pauseButton, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), stopButton, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), prevButton, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), nextButton, FALSE, FALSE, 3);

    gtk_widget_show(connectButton);
    gtk_widget_show(playButton);
    gtk_widget_show(pauseButton);
    gtk_widget_show(stopButton);
    gtk_widget_show(nextButton);
    gtk_widget_show(prevButton);

    progress = gtk_progress_bar_new();

    playQueuestore = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    pqTree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(playQueuestore));
//    gtk_tree_view_set_fixed_height_mode ((GtkTreeView *) pqTree, true);
//    gtk_tree_view_set_vadjustment((GtkTreeView*) pqTree, GTK_ADJUSTMENT(gtk_adjustment_new(0,0,100,1,10,100)));
    pqTreeScrollWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pqTreeScrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Title",
                                                   renderer,
                                                   "text", TITLE_COLUMN,
                                                   NULL);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Album",
                                                   renderer,
                                                   "text", ALBUM_COLUMN,
                                                   NULL);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    renderer = gtk_cell_renderer_text_new ();
    // g_object_set (renderer, "mode", GTK_CELL_RENDERER_MODE_ACTIVATABLE, NULL);
    column = gtk_tree_view_column_new_with_attributes ("Artist",
                                                   renderer,
                                                   "text", ARTIST_COLUMN,
                                                   NULL);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(column), true);
    gtk_tree_view_append_column (GTK_TREE_VIEW (pqTree), column);

    g_signal_connect (pqTree, "row-activated", (GCallback) activate_cb, this);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pqTreeScrollWindow), pqTree);
    gtk_widget_show(pqTree);


    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 2);

    gtk_box_pack_start (GTK_BOX (vbox), box, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (vbox), progress, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (vbox), pqTreeScrollWindow, true, true, 3);

    gtk_widget_show(box);
    gtk_widget_show(progress);
    gtk_widget_show(pqTreeScrollWindow);



    gtk_widget_show(vbox);


    gtk_container_add(GTK_CONTAINER(window), vbox);
}

void MainWindow::show()
{
    gtk_widget_show(window);
}

void MainWindow::updateProgress()
{
    float posF = static_cast<float>(m_cachedPosition)/static_cast<float>(m_cachedDuration);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress), posF);

    char buff[60];
    std::snprintf(buff, 59, "%u:%02u/%u:%02u", m_cachedPosition/60, m_cachedPosition%60, m_cachedDuration/60, m_cachedDuration%60);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress),buff);
}


void MainWindow::OnConnect()
{
    std::vector<std::string> taglist = {"vocal"};
    auto tracksReq = m_client.getTracks("", taglist, 0);
    auto tracks = tracksReq->next();
    std::cout << "================== " << tracksReq->pageNumber() << " ================\n";
    // for (const auto& track: tracks) {
    //     std::cout << track;
    // }
    fillPQList(tracks);
}
