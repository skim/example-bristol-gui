#ifndef BG_OPTION_H_
#define BG_OPTION_H_

#include <glib.h>

typedef enum {
	BG_OPTION_TYPE_NONE,
	BG_OPTION_TYPE_STRING,
	BG_OPTION_TYPE_INT
} BgOptionType;

typedef struct {
	BgOptionType type;
	char *key; 		//unique key
	char *name; 	//readable name
	char *option;   //cmd option (like -alsa)
} BgOption;

typedef struct {
	BgOptionType type;
	char *key;
	char *name;
	char *option;
	char *value;
} BgStringOption;

typedef struct {
	BgOptionType type;
	char *key;
	char *name;
	char *option;
	int value;
} BgIntOption;

typedef struct {
	GList *options;
	GHashTable *table;
	BgOption *selected;
} BgOptionList;

typedef struct {
	GList *choices;
} BgOptionChoiceList;

typedef struct {
	char *command;
} BgCommand;


#define BG_OPTION(option) ((BgOption*) option)
#define BG_STRING_OPTION(option) ((BgStringOption*) bg_option_check((BgOption*)option, BG_OPTION_TYPE_STRING))
#define BG_INT_OPTION(option) ((BgIntOption*) bg_option_check((BgOption*)option, BG_OPTION_TYPE_INT))

BgOption* 		bg_empty_option_new(const char *key, const char *name, const char *option);
BgOption* 		bg_option_check(BgOption *option, BgOptionType type);
char*			bg_option_commandline(BgOption *option);
BgOption* 		bg_string_option_new(const char *key, const char *name, const char *value);
void			bg_string_option_set(BgOption *option, const char *value);
BgOption*		bg_int_option_new(const char *key, const char *name, int value);
void			bg_int_option_set(BgOption *option, int value);

BgOptionChoiceList*	bg_option_choice_list_new();
void				bg_option_choice_list_add(BgOptionChoiceList *list, BgOption *option, int index);
void				bg_option_choice_list_add_all(BgOptionChoiceList *list, BgOptionChoiceList *list_to_add);
void				bg_option_choice_list_remove(BgOptionChoiceList *list, int index);
BgOption*			bg_option_choide_list_get(BgOptionChoiceList *list, int index);

BgOptionList* 	bg_option_list_new();
void 			bg_option_list_add(BgOptionList *list, BgOption *option);
BgOption* 		bg_option_list_get(BgOptionList *list, const char *key);
void 			bg_option_list_select(BgOptionList *list, const char *key);
BgCommand*		bg_command_new(const char *name, BgOptionList *list);

#endif /* BG_OPTION_H_ */
