#include "lg_option.h"
#include <glib.h>

LgOption* lg_option_new(const char *flag, const char *category, const char *name) {
	g_assert(flag != NULL);
	LgOption *option = g_new(LgOption, 1);
	option->type = LG_TYPE_OPTION;
	option->flag = g_strdup(flag);
	if (category != NULL) {
		option->category = g_strdup(category);
	}
	if (name != NULL) {
		option->name = g_strdup(name);
	}
	return option;
}

LgOption* lg_string_option_new(const char *flag, const char *category, const char *name, const char *value) {
	g_assert(flag != NULL);
	g_assert(value != NULL);
	LgStringOption *option = g_new(LgStringOption, 1);
	option->type = LG_TYPE_STRING_OPTION;
	option->flag = g_strdup(flag);
	option->value = g_strdup(value);
	if (category != NULL) {
		option->category = g_strdup(category);
	}
	if (name != NULL) {
		option->name = g_strdup(name);
	}
	return LG_OPTION(option);
}

