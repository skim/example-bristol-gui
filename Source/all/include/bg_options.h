#ifndef BG_OPTIONS_H_
#define BG_OPTIONS_H_

#include "lg.h"

LgOption* 	bg_engine_option_new(const char *value, const char *name);
GList*		bg_engine_options_new();


#endif /* BG_OPTIONS_H_ */
