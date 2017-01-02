/*
 * @file         plugin.cc
 * @author       Arthur Fait
 * @date         31.08.15
 *
 */

#include "plugin.h"

#include <gtk/gtk.h>
#include "soundcloud_widget.h" 

static SoundCloudWidget* sCWidget = NULL;

int plugin_init(void)
{
   sCWidget = new SoundCloudWidget();
   return true;
}
 
void *plugin_get_widget(void)
{
   GtkWidget *frame = gtk_frame_new(0);
   gtk_frame_set_shadow_type((GtkFrame*)frame, GTK_SHADOW_NONE);
   gtk_container_add((GtkContainer*)frame, sCWidget->content());
   return frame;
}

void plugin_cleanup(void)
{
   delete sCWidget;
   sCWidget = 0;
}
