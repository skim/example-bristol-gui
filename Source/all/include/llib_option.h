#ifndef LLIB_OPTION_H_
#define LLIB_OPTION_H_

#include "glib.h"
#include "llib_common.h"
#include "llib_value.h"

typedef struct _LOption 	LOption;
typedef struct _LOptionList LOptionList;

LOption*		l_option_new_string				(const char *id, const char *flag);
LOption*		l_option_new_int				(const char *id, const char *flag);
LType			l_option_get_type				(LOption *option);

LOptionList*	l_option_list_new				();
void			l_option_list_put_option		(LOptionList *list, LOption *option);
LOption*		l_option_list_get_option		(LOptionList *list, const char *id);
LOption* 		l_option_list_nth_option		(LOptionList *list, int index);
void			l_option_list_set_value			(LOptionList *list, const char *id, LValue *value);
LValue*			l_option_list_get_value			(LOptionList *list, const char *id);
int				l_option_list_length_options	(LOptionList *list);
int 			l_option_list_length_values		(LOptionList *list);
const char*		l_option_list_render_cli		(LOptionList *list);

#endif /* LLIB_OPTION_H_ */
