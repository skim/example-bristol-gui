#ifndef BG_COMMON_BASIC_H_
#define BG_COMMON_BASIC_H_

#include <glib.h>

typedef struct {
	char *name;
	char *value;
} BgEntry;

typedef struct {
	GList *list;
} BgEntryList;

char*			bg_make_path(const char *filename);
BgEntry* 		bg_entry_new(const char *name, const char *value);
BgEntryList*	bg_entry_list_new();
BgEntry* 		bg_entry_list_nth(BgEntryList *entries, int index);
void 			bg_entry_list_add(BgEntryList *entries, BgEntry *entry);
void 			bg_entry_list_add_new(BgEntryList *entries, const char *name, const char *value);

#endif /* BG_COMMON_BASIC_H_ */
