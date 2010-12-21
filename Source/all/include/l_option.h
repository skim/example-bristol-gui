#ifndef L_OPTION_H_
#define L_OPTION_H_

#include "bg_config.h"
#include "glib.h"

typedef enum {
	L_OPTION_TYPE_STRING,
	L_OPTION_TYPE_INT
} LOptionType;

typedef struct {
	LOptionType type;
	int index;
	char *id;
	char *flag;
} LOption;

typedef struct {
	LOptionType type;
	char *value_string;
	int	value_int;
} LOptionValue;

typedef struct {
	GList *options;
	GHashTable *map_options;
	GHashTable *map_values;
} LOptionList;

LOption*		l_option_new_string				(const char *id, const char *flag);
LOption*		l_option_new_int				(const char *id, const char *flag);
LOptionList*	l_option_list_new				();
void			l_option_list_put_option		(LOptionList *list, LOption *option);
LOption*		l_option_list_get_option		(LOptionList *list, const char *id);
LOption* 		l_option_list_nth_option		(LOptionList *list, int index);
void			l_option_list_set_value_string	(LOptionList *list, const char *id, const char *value);
void			l_option_list_set_value_int		(LOptionList *list, const char *id, int value);
LOptionValue*	l_option_list_get_value			(LOptionList *list, const char *id);
int				l_option_list_length_options	(LOptionList *list);
int 			l_option_list_length_values		(LOptionList *list);
char*			l_option_list_render_cli		(LOptionList *list);

#endif /* L_OPTION_H_ */
