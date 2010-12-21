#include "l_option.h"
#include <string.h>

struct _LOption {
	LType type;
	int index;
	char *id;
	char *flag;
};

struct _LValue {
	LType type;
	char *value_string;
	int value_int;
};

struct _LOptionList {
	GList *options;
	GHashTable *map_options;
	GHashTable *map_values;
};

static LOption* l_option_new(LType type, const char *id, const char *flag) {
	LOption *option = g_new(LOption, 1);
	option->type = type;
	option->id = g_strdup(id);
	if (flag != NULL) {
		option->flag = g_strdup(flag);
	}
	return option;
}

LOption* l_option_new_string(const char *id, const char *flag) {
	return l_option_new(L_TYPE_STRING, id, flag);
}
LOption* l_option_new_int(const char *id, const char *flag) {
	return l_option_new(L_TYPE_INT, id, flag);
}

LType l_option_get_type(LOption *option) {
	return option->type;
}

static LValue* l_option_value_new(LType type) {
	LValue *value = g_new(LValue, 1);
	value->type = type;
	return value;
}

LValue* l_value_new_string(const char *value) {
	LValue *option_value = l_option_value_new(L_TYPE_STRING);
	option_value->value_string = g_strdup(value);
	return option_value;
}

LValue* l_value_new_int(int value) {
	LValue *option_value = l_option_value_new(L_TYPE_INT);
	option_value->value_int = value;
	return option_value;
}

LType l_value_get_type(LValue *value) {
	return value->type;
}

void l_value_set_string(LValue *value, const char *string) {
	if (value->type != L_TYPE_STRING) {
		g_warning("value is not of type L_TYPE_STRING");
	} else {
		value->value_string = g_strdup(string);
	}
}

const char* l_value_get_string(LValue *value) {
	if (value->type != L_TYPE_STRING) {
		g_warning("value is not of type L_TYPE_STRING");
	} else {
		return g_strdup(value->value_string);
	}
	return NULL;
}

void l_value_set_int(LValue *value, int int_) {
	if (value->type != L_TYPE_INT) {
		g_warning("value is not of type L_TYPE_INT");
	} else {
		value->value_int = int_;
	}

}

int l_value_get_int(LValue *value) {
	if (value->type != L_TYPE_INT) {
		g_warning("value is not of type L_TYPE_INT");
	} else {
		return value->value_int;
	}
	return L_INT_UNDEFINED;

}

LOptionList* l_option_list_new() {
	LOptionList *list = g_new(LOptionList, 1);
	list->options = NULL;
	list->map_options = g_hash_table_new(g_str_hash, g_str_equal);
	list->map_values = g_hash_table_new(g_str_hash, g_str_equal);
	return list;
}

void l_option_list_put_option(LOptionList *list, LOption *option) {
	LOption *old_option = l_option_list_get_option(list, option->id);
	if (old_option != NULL) {
		g_hash_table_remove(list->map_options, option->id);
		list->options = g_list_remove(list->options, old_option);
		list->options = g_list_insert(list->options, option, old_option->index);
		option->index = old_option->index;
	} else {
		list->options = g_list_append(list->options, option);
		option->index = g_list_length(list->options) - 1;
	}
	g_hash_table_insert(list->map_options, option->id, option);
}

LOption* l_option_list_get_option(LOptionList *list, const char *id) {
	return (LOption*) g_hash_table_lookup(list->map_options, id);
}

LOption* l_option_list_nth_option(LOptionList *list, int index) {
	return (LOption*) g_list_nth_data(list->options, index);
}

int l_option_list_length_options(LOptionList *list) {
	return g_list_length(list->options);
}

int l_option_list_length_values(LOptionList *list) {
	return g_hash_table_size(list->map_options);
}

void l_option_list_set_value(LOptionList *list, const char *id, LValue *value) {
	LOption *option = l_option_list_get_option(list, id);
	if (option == NULL) {
	} else if (option->type != value->type) {
		g_warning("option type does not match value type");
	} else {
		g_hash_table_insert(list->map_values, g_strdup(id), value);
	}
}

LValue* l_option_list_get_value(LOptionList *list, const char *id) {
	return (LValue*) g_hash_table_lookup(list->map_values, id);
}

const char* l_option_list_render_cli(LOptionList *list) {
	char *cli = "";
	int i;
	for (i = 0; i < l_option_list_length_options(list); i++) {
		LOption *option = l_option_list_nth_option(list, i);
		LValue *value = l_option_list_get_value(list, option->id);
		if (value != NULL) {
			cli = g_strconcat(cli, " -", NULL);
			if (option->flag != NULL) {
				cli = g_strconcat(cli, option->flag, " ", NULL);
			}
			switch (value->type) {
			case L_TYPE_STRING:
				cli = g_strconcat(cli, value->value_string, NULL);
				break;
			case L_TYPE_INT:
				cli = g_strdup_printf("%s%d", cli, value->value_int);
				break;
			default:
				break;
			}
		}
	}
	if (strlen(cli) > 2) {
		cli = g_strstrip(cli);
	}
	return cli;
}
