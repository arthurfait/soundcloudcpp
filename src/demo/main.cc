#include <stdlib.h>
#include <gtk/gtk.h>
#include <string>
#include <vector>
#include <client.h>

#include "main_window.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    MainWindow mw;
    mw.show();
    std::vector<MainWindow::PQItem> testList;
    for (int i = 0; i < 20; i++) {
         testList.push_back(MainWindow::PQItem());
    }

     // mw.fillPQList(testList);
    gtk_main ();
    return 0;
}
