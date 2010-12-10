#include "bg_common_basic.h"
#include "bg_config.h"
#include "glib.h"

char* bg_path_new(const char *filename) {
	return g_strconcat(BG_PATH_DATA, "/", filename, NULL);
}

GListProxy* g_list_proxy_new() {
	GListProxy *proxy = g_new(GListProxy, 1);
	proxy->list = NULL;
	return proxy;
}
