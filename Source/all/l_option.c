#include "l_option.h"

static LOption* l_option_new(LOptionType type, const char *id, const char *flag) {
	LOption *option = g_new(LOption, 1);
	option->type = type;
	option->id = g_strdup(id);
	if (flag != NULL) {
		option->flag = g_strdup(flag);
	}
	return option;
}

static LOptionValue* l_option_value_new(LOption *option) {
	LOptionValue *value = g_new(LOptionValue, 1);
	value->type = option->type;
	return value;
}

LOption* l_option_new_string(const char *id, const char *flag) {
	return l_option_new(L_OPTION_TYPE_STRING, id, flag);
}
LOption* l_option_new_int(const char *id, const char *flag) {
	return l_option_new(L_OPTION_TYPE_INT, id, flag);
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

static LOptionValue* l_option_list_get_value(LOptionList *list, const char *id) {
	return (LOptionValue*) g_hash_table_lookup(list->map_values, id);
}

void l_option_list_set_value_string(LOptionList *list, const char *id, const char *value) {
	LOption *option = l_option_list_get_option(list, id);
	if (option == NULL) {
		g_warning("no option for id: %s", id);
	} else if (option->type != L_OPTION_TYPE_STRING) {
		g_warning("option: %s is not of type L_OPTION_TYPE_STRING", id);
	} else {
		LOptionValue *option_value = l_option_value_new(option);
		option_value->value_string = g_strdup(value);
		g_hash_table_insert(list->map_values, option->id, option_value);
	}
}

char* l_option_list_get_value_string(LOptionList *list, const char *id) {
	LOptionValue *value = l_option_list_get_value(list, id);
	if (value == NULL) {
	} else if (value->type != L_OPTION_TYPE_STRING) {
		g_warning("option: %s is not of type L_OPTION_TYPE_STRING", id);
	} else {
		return g_strdup(value->value_string);
	}
	return NULL;
}

int l_option_list_get_value_int(LOptionList *list, const char *id) {
	LOptionValue *value = l_option_list_get_value(list, id);
	if (value == NULL) {
	} else if (value->type != L_OPTION_TYPE_INT) {
		g_warning("option: %s is not of type L_OPTION_TYPE_INT", id);
	} else {
		return value->value_int;
	}
	return L_INT_UNDEFINED;
}


void l_option_list_set_value_int(LOptionList *list, const char *id, int value) {
	LOption *option = l_option_list_get_option(list, id);
	if (option == NULL) {
		g_warning("no option for id: %s", id);
	} else if (option->type != L_OPTION_TYPE_INT) {
		g_warning("option: %s is not of type L_OPTION_TYPE_INT", id);
	} else {
		LOptionValue *option_value = l_option_value_new(option);
		option_value->value_int = value;
		g_hash_table_insert(list->map_values, option->id, option_value);
	}
}

char* l_option_list_render_cli(LOptionList *list) {
	char *cli = "";
	int i;
	for (i = 0; i < l_option_list_length_options(list); i++) {
		LOption *option = l_option_list_nth_option(list, i);
		LOptionValue *value = l_option_list_get_value(list, option->id);
		if (value != NULL) {
			cli = g_strconcat(cli, " -", NULL);
			if (option->flag != NULL) {
				cli = g_strconcat(cli, option->flag, " ", NULL);
			}
			switch (value->type) {
				case L_OPTION_TYPE_STRING:
					cli = g_strconcat(cli, value->value_string, NULL);
					break;
				case L_OPTION_TYPE_INT:
					cli = g_strdup_printf("%s%d", cli, value->value_int);
					break;
				default:
					break;
			}
		}
	}
	g_strstrip(cli);
	return cli;
}
