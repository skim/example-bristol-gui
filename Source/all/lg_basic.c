#include "lg_basic.h"

#include <glib.h>

LgObject* lg_object_check(LgObject *object, LgType type) {
	g_assert(object != NULL);
	g_assert(object->type == type);
	return object;
}

LgStringHashList* lg_hash_list_new() {
	LgStringHashList *hlist = g_new(LgStringHashList, 1);
	hlist->type = LG_TYPE_STRING_HASH_LIST;
	hlist->list = NULL;
	hlist->table = g_hash_table_new(g_str_hash, g_str_equal);
	return hlist;
}

void lg_hash_list_add(LgStringHashList *list, const char *key, gpointer value) {
	lg_object_check(LG_OBJECT(list), LG_TYPE_STRING_HASH_LIST);
	int index = -1;
	if (g_hash_table_lookup(list->table, key) != NULL) {
		index = g_list_index(list->list, g_hash_table_lookup(list->table, key));
		list->list = g_list_remove(list->list, g_hash_table_lookup(list->table, key));
	}
	g_hash_table_insert(list->table, g_strdup(key), value);
	if (index == -1) {
		list->list = g_list_insert(list->list, value, index);
	} else {
		list->list = g_list_append(list->list, value);
	}
}

gpointer lg_hash_list_lookup(LgStringHashList *list, const char *key) {
	lg_object_check(LG_OBJECT(list), LG_TYPE_STRING_HASH_LIST);
	return g_hash_table_lookup(list->table, key);
}

gpointer lg_hash_list_get(LgStringHashList *list, int index) {
	lg_object_check(LG_OBJECT(list), LG_TYPE_STRING_HASH_LIST);
	return g_list_nth_data(list->list, index);
}

void lg_hash_list_foreach(LgStringHashList *list, GFunc func, gpointer data) {
	lg_object_check(LG_OBJECT(list), LG_TYPE_STRING_HASH_LIST);
	g_list_foreach(list->list, func, data);
}

