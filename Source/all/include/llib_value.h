#ifndef LLIB_VALUE_H_
#define LLIB_VALUE_H_

#include "glib.h"
#include "llib_common.h"

typedef struct _LValue		LValue;
typedef struct _LValueList	LValueList;

LValue* 	l_value_new_string				(const char *value);
LValue* 	l_value_new_int					(int value);
LType		l_value_get_type				(LValue *value);
void		l_value_set_string				(LValue *value, const char *string);
const char*	l_value_get_string				(LValue *value);
void		l_value_set_int					(LValue *value, int int_);
int			l_value_get_int					(LValue *value);

LValueList*	l_value_list_new_string			();
int			l_value_list_length				(LValueList *list);
LType		l_value_list_get_type			(LValueList *list);
void		l_value_list_put_value			(LValueList *list, const char *display_name, LValue *value);
LValue*		l_value_list_get_value			(LValueList *list, const char *display_name);
LValue*		l_value_list_nth_value			(LValueList *list, int index);
const char*	l_value_list_nth_display_name	(LValueList *list, int index);

#endif /* LLIB_VALUE_H_ */
