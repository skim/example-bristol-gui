#include "bg_common.h"
#include "bg_config.h"
#include <glib.h>

char *bg_make_path(const char *filename) {
	return g_strdup_printf("%s/%s", BG_DATA_PATH, filename);
}

BgEntry* bg_entry_new(const char *name, const char *value) {
	BgEntry *entry = g_new(BgEntry, 1);
	entry->name = g_strdup(name);
	entry->value = g_strdup(value);
	return entry;
}

BgEntryList *bg_entry_list_new() {
	BgEntryList *list = g_new(BgEntryList, 1);
	list->list = NULL;
	return list;
}

void bg_entry_list_add(BgEntryList *entries, BgEntry *entry) {
	entries->list = g_list_append(entries->list, entry);
}

void bg_entry_list_add_new(BgEntryList *entries, const char *name, const char *value) {
	bg_entry_list_add(entries, bg_entry_new(name, value));
}

BgEntry* bg_entry_list_nth(BgEntryList *entries, int index) {
	return (BgEntry*) g_list_nth_data(entries->list, index);
}

BgOption* bg_option_new(const char *id, gboolean has_flag, BgOptionType type) {
	BgOption *option = g_new(BgOption, 1);
	option->id = g_strdup(id);
	option->has_flag = has_flag;
	option->type = type;
	return option;
}

BgOption* bg_option_new_string(const char *id, gboolean has_flag, const char *value) {
	BgOption *option = bg_option_new(id, has_flag, BG_OPTION_STRING);
	option->value_string = g_strdup(value);
	return option;
}

BgOptionList* bg_option_list_new() {
	BgOptionList *options = g_new(BgOptionList, 1);
	options->list = NULL;
	options->map = g_hash_table_new(g_str_hash, g_str_equal);
	return options;
}

void bg_option_list_add(BgOptionList *list, BgOption *option) {
	list->list = g_list_append(list->list, option);
	g_hash_table_insert(list->map, option->id, option);
}

BgOption* bg_option_list_get(BgOptionList *list, const char *id) {
	return (BgOption*) g_hash_table_lookup(list->map, id);
}

void bg_option_list_remove(BgOptionList *list, BgOption *option) {
	g_hash_table_remove(list->map, option->id);
	list->list = g_list_remove(list->list, option);
}
