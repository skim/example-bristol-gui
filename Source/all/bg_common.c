#include "bg_common.h"
#include "bg_config.h"
#include <glib.h>

char *bg_make_path(const char *filename) {
	return g_strdup_printf("%s/%s", BG_DATA_PATH, filename);
}

BgComboEntry* bg_combo_entry_new(const char *name, const char *value) {
	BgComboEntry *entry = g_new(BgComboEntry, 1);
	entry->name = g_strdup(name);
	entry->value = g_strdup(value);
	return entry;
}
