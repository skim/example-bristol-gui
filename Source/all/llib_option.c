#include "llib_option.h"
#include <string.h>

struct _LOption {
	LType type;
	int index;
	char *id;
	char *flag;
};

struct _LOptionList {
	GList *options;
	GHashTable *map_options;
	GHashTable *map_values;
};

static LOption* l_option_new(LType type, const char *id, const char *flag) {
	g_assert(id != NULL && strlen(id) > 0);
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

LOptionList* l_option_list_new() {
	LOptionList *list = g_new(LOptionList, 1);
	list->options = NULL;
	list->map_options = g_hash_table_new(g_str_hash, g_str_equal);
	list->map_values = g_hash_table_new(g_str_hash, g_str_equal);
	return list;
}

void l_option_list_put_option(LOptionList *list, LOption *option) {
	g_assert(list != NULL);
	g_assert(option != NULL);
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
	g_assert(list != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	return (LOption*) g_hash_table_lookup(list->map_options, id);
}

LOption* l_option_list_nth_option(LOptionList *list, int index) {
	g_assert(list != NULL);
	return (LOption*) g_list_nth_data(list->options, index);
}

int l_option_list_length_options(LOptionList *list) {
	g_assert(list != NULL);
	return g_list_length(list->options);
}

int l_option_list_length_values(LOptionList *list) {
	g_assert(list != NULL);
	return g_hash_table_size(list->map_options);
}

void l_option_list_set_value(LOptionList *list, const char *id, LValue *value) {
	g_assert(list != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	g_assert(value != NULL);
	LOption *option = l_option_list_get_option(list, id);
	if (option == NULL) {
	} else if (option->type != l_value_get_type(value)) {
		g_warning("option type does not match value type");
	} else {
		g_hash_table_insert(list->map_values, g_strdup(id), value);
	}
}

LValue* l_option_list_get_value(LOptionList *list, const char *id) {
	g_assert(list != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	return (LValue*) g_hash_table_lookup(list->map_values, id);
}

const char* l_option_list_render_cli(LOptionList *list) {
	g_assert(list != NULL);
	char *cli = "";
	int i;
	for (i = 0; i < l_option_list_length_options(list); i++) {
		LOption *option = l_option_list_nth_option(list, i);
		LValue *value = l_option_list_get_value(list, option->id);
		if (value != NULL && l_value_is_enabled(value)) {
			cli = g_strconcat(cli, " -", NULL);
			if (option->flag != NULL) {
				cli = g_strconcat(cli, option->flag, " ", NULL);
			}
			switch (l_value_get_type(value)) {
			case L_TYPE_STRING:
				cli = g_strconcat(cli, l_value_get_string(value), NULL);
				break;
			case L_TYPE_INT:
				cli = g_strdup_printf("%s%d", cli, l_value_get_int(value));
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
