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

BgOption* bg_option_new(const char *id, BgOptionType type) {
	BgOption *option = g_new(BgOption, 1);
	option->id = g_strdup(id);
	option->type = type;
	option->flag = NULL;
	return option;
}

BgOption* bg_option_new_string(const char *id, const char *value) {
	BgOption *option = bg_option_new(id, BG_OPTION_STRING);
	option->value_string = g_strdup(value);
	return option;
}

BgOption* bg_option_new_int(const char *id, int value) {
	BgOption *option = bg_option_new(id, BG_OPTION_INT);
	option->value_int = value;
	return option;
}

char* bg_option_render(BgOption *option) {
	char *string = "-";
	if (option->flag != NULL) {
		string = g_strconcat(string, option->flag, " ", NULL);
	}
	switch (option->type) {
		case BG_OPTION_INT:
			string = g_strconcat(string, g_strdup_printf("%d", option->value_int), NULL);
			break;
		case BG_OPTION_STRING:
			string = g_strconcat(string, option->value_string, NULL);
			break;
		default:
			break;
	}
	return string;

}

BgOptionList* bg_option_list_new() {
	BgOptionList *options = g_new(BgOptionList, 1);
	options->list = NULL;
	options->map = g_hash_table_new(g_str_hash, g_str_equal);
	options->map_flags = g_hash_table_new(g_str_hash, g_str_equal);
	return options;
}

void bg_option_list_add_flag(BgOptionList *list, const char *option_id, const char *flag) {
	g_hash_table_insert(list->map_flags, g_strdup(option_id), g_strdup(flag));
}

void bg_option_list_add(BgOptionList *list, BgOption *option) {
	list->list = g_list_append(list->list, option);
	g_hash_table_insert(list->map, option->id, option);
	if (g_hash_table_lookup(list->map_flags, option->id) != NULL) {
		option->flag = (char*) g_hash_table_lookup(list->map_flags, option->id);
	}
}

BgOption* bg_option_list_get(BgOptionList *list, const char *id) {
	return (BgOption*) g_hash_table_lookup(list->map, id);
}

void bg_option_list_remove(BgOptionList *list, BgOption *option) {
	g_hash_table_remove(list->map, option->id);
	list->list = g_list_remove(list->list, option);
}

char* bg_option_list_render(BgOptionList *list) {
	char *string = "";
	int i;
	for (i = 0; i < g_list_length(list->list); i++) {
		BgOption *option = (BgOption*) g_list_nth_data(list->list, i);
		string = g_strconcat(string, " ", bg_option_render(option), NULL);
	}
	return string;
}

