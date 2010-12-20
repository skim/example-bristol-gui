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
	char *id;
	char *flag;
	char *widget_type;
} BgOptionConfig;

typedef struct {
	char *id;
	BgOptionType type;
	BgOptionConfig *config;
	gboolean active;
	char *value_string;
	int value_int;
} BgOption;

typedef struct {
	GList *list;
	GHashTable *map;
	GList *configs;
	GHashTable *map_configs;
} BgOptionList;

char*			bg_make_path					(const char *filename);
BgEntry* 		bg_entry_new					(const char *name, const char *value);
BgEntryList*	bg_entry_list_new				();
BgEntry* 		bg_entry_list_nth				(BgEntryList *entries, int index);
void 			bg_entry_list_add				(BgEntryList *entries, BgEntry *entry);
void 			bg_entry_list_add_new			(BgEntryList *entries, const char *name, const char *value);
BgOptionConfig* bg_option_config_new			(const char *id, const char *widget_type, const char *flag);
BgOption* 		bg_option_new					(const char *id, BgOptionType type);
BgOption* 		bg_option_new_string			(const char *id, const char *value);
BgOption* 		bg_option_new_int				(const char *id, int value);
BgOptionList* 	bg_option_list_new				();
int				bg_option_list_length			(BgOptionList *list);
int				bg_option_list_config_length	(BgOptionList *list);
BgOptionConfig*	bg_option_list_get_config		(BgOptionList *list, const char *option_id);
void			bg_option_list_add_config		(BgOptionList *list, BgOptionConfig *config);
void 			bg_option_list_add				(BgOptionList *list, BgOption *option);
BgOption* 		bg_option_list_get				(BgOptionList *list, const char *id);
BgOption* 		bg_option_list_get_nth			(BgOptionList *list, int index);
BgOptionConfig*	bg_option_list_get_nth_config	(BgOptionList *list, int index);
void 			bg_option_list_remove			(BgOptionList *list, BgOption *option);
char*			bg_option_list_render			(BgOptionList *list);

#endif /* BG_COMMON_BASIC_H_ */
