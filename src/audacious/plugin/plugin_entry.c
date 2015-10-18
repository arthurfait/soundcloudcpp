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
   .about_text = "SoundCloud plugin 0.2 by konqwenqor. \n\nCopyright © 2014-2015 Arthur Fait <konqwenqor@gmail.com>.\n\nFor search by tag put '# in front of query.\nFor search by genre put '@' in front of query.",
   .init = plugin_init,
   .cleanup = plugin_cleanup,
   .get_widget = plugin_get_widget
)
