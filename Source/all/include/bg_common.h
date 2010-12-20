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

typedef enum {
	BG_OPTION_STRING,
	BG_OPTION_INT
} BgOptionType;

typedef struct {
	BgOptionType type;
	gboolean has_flag;
	char *id;
	char *value_string;
	int value_int;
} BgOption;

typedef struct {
	GList *list;
	GHashTable *map;
} BgOptionList;

char*			bg_make_path(const char *filename);
BgEntry* 		bg_entry_new(const char *name, const char *value);
BgEntryList*	bg_entry_list_new();
BgEntry* 		bg_entry_list_nth(BgEntryList *entries, int index);
void 			bg_entry_list_add(BgEntryList *entries, BgEntry *entry);
void 			bg_entry_list_add_new(BgEntryList *entries, const char *name, const char *value);
BgOption* 		bg_option_new(const char *id, gboolean has_flag, BgOptionType type);
BgOption* 		bg_option_new_string(const char *id, gboolean has_flag, const char *value);
BgOption* 		bg_option_new_int(const char *id, gboolean has_flag, int value);
BgOptionList* 	bg_option_list_new();
void 			bg_option_list_add(BgOptionList *list, BgOption *option);
BgOption* 		bg_option_list_get(BgOptionList *list, const char *id);
void 			bg_option_list_remove(BgOptionList *list, BgOption *option);

#endif /* BG_COMMON_BASIC_H_ */
