#ifndef LG_BASIC_H_
#define LG_BASIC_H_

#include <glib.h>

typedef enum {
	LG_TYPE_STRING_HASH_LIST,
	LG_TYPE_OPTION,
	LG_TYPE_STRING_OPTION,
	LG_TYPE_INT_OPTION
} LgType;

typedef struct {
	LgType type;
} LgObject;

typedef struct {
	LgType type;
	GList *list;
	GHashTable *table;
} LgStringHashList;

#define LG_OBJECT(instance) ((LgObject*)instance)
#define LG_STRING_HASH_LIST(instance) ((LgStringHashList*)lg_object_check(LG_OBJECT(instance), LG_TYPE_STRING_HASH_LIST))

LgObject* 			lg_object_check(LgObject *object, LgType type);
LgStringHashList* 	lg_hash_list_new();
void				lg_hash_list_add(LgStringHashList *list, const char *key, gpointer value);
gpointer			lg_hash_list_lookup(LgStringHashList *list, const char *key);
gpointer			lg_hash_list_get(LgStringHashList *list, int index);
void				lg_hash_list_foreach(LgStringHashList *list, GFunc func, gpointer data);

#endif /* LG_BASIC_H_ */
