#ifndef PLUGIN_H
#define PLUGIN_H

#ifdef __cplusplus
extern "C" {
#endif

int plugin_init(void);
void *plugin_get_widget(void);
void plugin_cleanup(void);

#ifdef __cplusplus
}
#endif


#endif // PLUGIN_H


