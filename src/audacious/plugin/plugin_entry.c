/*
 * @file         plugin_entry.c
 * @author       Arthur Fait
 * @date         31.08.15
 *
 */

#include <audacious/plugin.h>
#include <libaudcore/audstrings.h>

#include "plugin.h"

AUD_GENERAL_PLUGIN
(
   .name = "SoundCloud",
   .domain = "soundcloud",
   .init = plugin_init,
   .cleanup = plugin_cleanup,
   .get_widget = plugin_get_widget
)
