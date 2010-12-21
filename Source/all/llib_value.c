#include "llib_value.h"
#include <string.h>

typedef struct {
	LValue *value;
	int index;
	char *display_name;
} LValueWrapper;

struct _LValue {
	LType type;
	char *value_string;
	int value_int;
};

struct _LValueList {
	LType type;
	GList *value_wrappers;
	GHashTable *map_value_wrappers;
};

static LValueWrapper* l_value_wrapper_new(LValue *value, const char *display_name) {
	g_assert(value != NULL);
	g_assert(display_name != NULL && strlen(display_name) > 0);
	LValueWrapper *wrapper = g_new(LValueWrapper, 1);
	wrapper->value = value;
	wrapper->display_name = g_strdup(display_name);
	return wrapper;
}

static LValue* l_value_new(LType type) {
	LValue *value = g_new(LValue, 1);
	value->type = type;
	return value;
}

LValue* l_value_new_string(const char *value) {
	g_assert(value != NULL && strlen(value) > 0);
	LValue *option_value = l_value_new(L_TYPE_STRING);
	option_value->value_string = g_strdup(value);
	return option_value;
}

LValue* l_value_new_int(int value) {
	LValue *option_value = l_value_new(L_TYPE_INT);
	option_value->value_int = value;
	return option_value;
}

LType l_value_get_type(LValue *value) {
	return value->type;
}

void l_value_set_string(LValue *value, const char *string) {
	g_assert(value != NULL);
	g_assert(string != NULL && strlen(string) > 0);
	if (value->type != L_TYPE_STRING) {
		g_warning("value is not of type L_TYPE_STRING");
	} else {
		value->value_string = g_strdup(string);
	}
}

const char* l_value_get_string(LValue *value) {
	g_assert(value != NULL);
	if (value->type != L_TYPE_STRING) {
		g_warning("value is not of type L_TYPE_STRING");
	} else {
		return g_strdup(value->value_string);
	}
	return NULL;
}

void l_value_set_int(LValue *value, int int_) {
	g_assert(value != NULL);
	if (value->type != L_TYPE_INT) {
		g_warning("value is not of type L_TYPE_INT");
	} else {
		value->value_int = int_;
	}

}

int l_value_get_int(LValue *value) {
	g_assert(value != NULL);
	if (value->type != L_TYPE_INT) {
		g_warning("value is not of type L_TYPE_INT");
	} else {
		return value->value_int;
	}
	return L_INT_UNDEFINED;

}

LValueList* l_value_list_new(LType type) {
	LValueList *list = g_new(LValueList, 1);
	list->type = type;
	list->value_wrappers = NULL;
	list->map_value_wrappers = g_hash_table_new(g_str_hash, g_str_equal);
	return list;
}

LType l_value_list_get_type(LValueList *list) {
	g_assert(list != NULL);
	return list->type;
}

int l_value_list_length(LValueList *list) {
	g_assert(list != NULL);
	return g_list_length(list->value_wrappers);
}

LValueList* l_value_list_new_string() {
	return l_value_list_new(L_TYPE_STRING);
}

static LValueWrapper* l_value_list_get_wrapper(LValueList *list, const char *display_name) {
	g_assert(list != NULL);
	g_assert(display_name != NULL && strlen(display_name) > 0);
	return (LValueWrapper*) g_hash_table_lookup(list->map_value_wrappers, display_name);
}

static LValueWrapper* l_value_list_nth_wrapper(LValueList *list, int index) {
	g_assert(list != NULL);
	return (LValueWrapper*) g_list_nth_data(list->value_wrappers, index);
}

void l_value_list_put_value(LValueList *list, const char *display_name, LValue *value) {
	g_assert(list != NULL);
	g_assert(display_name != NULL && strlen(display_name) > 0);
	g_assert(value != NULL);
	if (list->type != value->type) {
		g_warning("type of value list and type of value do not match");
	} else {
		LValueWrapper *wrapper = l_value_list_get_wrapper(list, display_name);
		if (wrapper != NULL) {
			wrapper->value = value;
		} else {
			wrapper = l_value_wrapper_new(value, display_name);
			list->value_wrappers = g_list_append(list->value_wrappers, wrapper);
			wrapper->index = l_value_list_length(list) - 1;
			g_hash_table_insert(list->map_value_wrappers, g_strdup(display_name), value);
		}

	}
}

LValue* l_value_list_get_value(LValueList *list, const char *display_name) {
	g_assert(list != NULL);
	g_assert(display_name != NULL && strlen(display_name) > 0);
	LValueWrapper *wrapper = l_value_list_get_wrapper(list, display_name);
	if (wrapper == NULL) {
		return NULL;
	} else {
		return wrapper->value;
	}
}

LValue* l_value_list_nth_value(LValueList *list, int index) {
	g_assert(list != NULL);
	LValueWrapper *wrapper = l_value_list_nth_wrapper(list, index);
	if (wrapper == NULL) {
		return NULL;
	} else {
		return wrapper->value;
	}
}

const char* l_value_list_nth_display_name(LValueList *list, int index) {
	g_assert(list != NULL);
	LValueWrapper *wrapper = l_value_list_nth_wrapper(list, index);
	if (wrapper == NULL) {
		return NULL;
	} else {
		return wrapper->display_name;
	}
}
