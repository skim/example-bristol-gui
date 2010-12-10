#ifndef BG_COMMON_BASIC_H_
#define BG_COMMON_BASIC_H_

#include "bg_config.h"
#include <glib.h>

typedef struct {
	GList *list;
} GListProxy;

char* bg_path_new(const char *filename);
GListProxy* g_list_proxy_new();

#endif /* BG_COMMON_BASIC_H_ */
