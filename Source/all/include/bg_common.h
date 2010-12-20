#ifndef BG_COMMON_BASIC_H_
#define BG_COMMON_BASIC_H_

#include <glib.h>

//TODO: options order?

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
	char *id;
	char *flag;
	char *value_string;
	int value_int;
} BgOption;

typedef struct {
	GList *list;
	GHashTable *map;
	GHashTable *map_flags;
} BgOptionList;

char*			bg_make_path			(const char *filename);
BgEntry* 		bg_entry_new			(const char *name, const char *value);
BgEntryList*	bg_entry_list_new		();
BgEntry* 		bg_entry_list_nth		(BgEntryList *entries, int index);
void 			bg_entry_list_add		(BgEntryList *entries, BgEntry *entry);
void 			bg_entry_list_add_new	(BgEntryList *entries, const char *name, const char *value);
BgOption* 		bg_option_new			(const char *id, BgOptionType type);
BgOption* 		bg_option_new_string	(const char *id, const char *value);
BgOption* 		bg_option_new_int		(const char *id, int value);
BgOptionList* 	bg_option_list_new		();
void 			bg_option_list_add_flag	(BgOptionList *list, const char *option_id, const char *flag);
void 			bg_option_list_add		(BgOptionList *list, BgOption *option);
BgOption* 		bg_option_list_get		(BgOptionList *list, const char *id);
void 			bg_option_list_remove	(BgOptionList *list, BgOption *option);
char*			bg_option_list_render	(BgOptionList *list);

#endif /* BG_COMMON_BASIC_H_ */
