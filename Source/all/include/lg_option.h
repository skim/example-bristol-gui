#ifndef LG_OPTION_H_
#define LG_OPTION_H_

#include "lg_basic.h"

typedef struct {
	LgType type;		// LG_TYPE_*
	char *flag;			// flag for CLI, ie -jack
	char *category;		// optional category
	char *name;			// optional readable name
} LgOption;

typedef struct {
	LgType type;
	char *flag;
	char *category;
	char *name;
	char *value;
} LgStringOption;

typedef struct {
	LgType type;
	char *flag;
	char *category;
	char *name;
	int value;
} LgIntOption;

#define LG_OPTION(instance) ((LgOption*)lg_object_check(LG_OBJECT(instance), LG_TYPE_OPTION))
#define LG_STRING_OPTION(instance) ((LgStringOption*)lg_object_check(LG_OBJECT(instance), LG_TYPE_STRING_OPTION))


LgObject* lg_object_check(LgObject *object, LgType type);
LgOption* lg_option_new(const char *flag, const char *category, const char *name);
LgOption* lg_string_option_new(const char *flag, const char *category, const char *name, const char *value);


#endif /* LG_OPTION_H_ */
