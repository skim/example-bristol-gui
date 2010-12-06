#ifndef GUI_H_
#define GUI_H_

#include "bg_configuration.h"

void bg_gui_prepare(const char *suffix);
void bg_gui_set(const char *suffix, bg_configuration *config);
void bg_gui_help_show(const char *text_name);
void bg_synth_start(const char *synth_name);

#endif /* GUI_H_ */
