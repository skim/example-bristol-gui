#include "bg_options.h"
#include "glib.h"
#include "string.h"

LgOption* bg_engine_option_new(const char *value, const char *name) {
	g_assert(value != NULL);
	g_assert(strlen(value) > 1);
	g_assert(name != NULL);
	g_assert(strlen(name) > 1);
	return lg_option_new(value, "engine", name);
}

GList* bg_engine_options_new() {
	GList *list = NULL;
	list = g_list_append(list, bg_engine_option_new("jack", "JACK"));
	list = g_list_append(list, bg_engine_option_new("alsa", "ALSA"));
	list = g_list_append(list, bg_engine_option_new("oss", "OSS"));
	return list;
}
