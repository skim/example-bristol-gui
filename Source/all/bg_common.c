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

