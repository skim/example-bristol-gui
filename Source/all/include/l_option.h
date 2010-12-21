#ifndef L_OPTION_H_
#define L_OPTION_H_

#include "bg_config.h"
#include "glib.h"

#define L_INT_UNDEFINED G_MAXINT

typedef enum {
	L_TYPE_STRING,
	L_TYPE_INT
} LType;

typedef struct _LOption 	LOption;
typedef struct _LValue 		LValue;
typedef struct _LOptionList LOptionList;

LOption*		l_option_new_string				(const char *id, const char *flag);
LOption*		l_option_new_int				(const char *id, const char *flag);
LType			l_option_get_type				(LOption *option);

LValue* 		l_value_new_string				(const char *value);
LValue* 		l_value_new_int					(int value);
LType			l_value_get_type				(LValue *value);
void			l_value_set_string				(LValue *value, const char *string);
const char*		l_value_get_string				(LValue *value);
void			l_value_set_int					(LValue *value, int int_);
int				l_value_get_int					(LValue *value);

LOptionList*	l_option_list_new				();
void			l_option_list_put_option		(LOptionList *list, LOption *option);
LOption*		l_option_list_get_option		(LOptionList *list, const char *id);
LOption* 		l_option_list_nth_option		(LOptionList *list, int index);
void			l_option_list_set_value			(LOptionList *list, const char *id, LValue *value);
LValue*			l_option_list_get_value			(LOptionList *list, const char *id);
int				l_option_list_length_options	(LOptionList *list);
int 			l_option_list_length_values		(LOptionList *list);
const char*		l_option_list_render_cli		(LOptionList *list);

#endif /* L_OPTION_H_ */
