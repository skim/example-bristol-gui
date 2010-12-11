#include "bg_option.h"

#include <glib.h>
#include <gtk/gtk.h>

BgOption* bg_empty_option_new(const char *key, const char *name, const char *_option) {
	BgOption *option = g_new(BgOption, 1);
	option->type = BG_OPTION_TYPE_NONE;
	option->key = g_strdup(key);
	option->name = g_strdup(name);
	option->option = g_strdup(_option);
	return option;
}

BgOption* bg_string_option_new(const char *key, const char *name, const char *value) {
	BgStringOption *option = g_new(BgStringOption, 1);
	option->type = BG_OPTION_TYPE_STRING;
	option->key = g_strdup(key);
	option->name = g_strdup(name);
	option->option = g_strdup(key);
	option->value = g_strdup(value);
	return BG_OPTION(option);
}

void bg_string_option_set(BgOption *option, const char *value) {
	BG_STRING_OPTION(option)->value = g_strdup(value);
}

BgOption* bg_int_option_new(const char *key, const char *name, int value) {
	BgIntOption *option = g_new(BgIntOption, 1);
	option->type = BG_OPTION_TYPE_INT;
	option->key = g_strdup(key);
	option->name = g_strdup(name);
	option->option = g_strdup(key);
	option->value = value;
	return BG_OPTION(option);
}

void bg_int_option_set(BgOption *option, int value) {
	BG_INT_OPTION(option)->value = value;
}

BgOption* bg_option_check(BgOption *option, BgOptionType type) {
	g_assert(option != NULL);
	g_assert(option->type == type);
	return option;
}

char* bg_option_commandline(BgOption *option) {
	switch (option->type) {
	case BG_OPTION_TYPE_NONE:
		return g_strdup_printf("-%s", option->option);
		break;
	case BG_OPTION_TYPE_STRING:
		return g_strdup_printf("-%s %s", option->option, BG_STRING_OPTION(option)->value);
		break;
	case BG_OPTION_TYPE_INT:
		return g_strdup_printf("-%s %d", option->option, BG_INT_OPTION(option)->value);
		break;
	default:
		g_warning("unknown option type for: %s", option->option);
		break;
	}
	return "";
}

BgOptionChoiceList* bg_option_choice_list_new() {
	BgOptionChoiceList *list = g_new(BgOptionChoiceList, 1);
	list->choices = NULL;
	return list;
}

void bg_option_choice_list_add(BgOptionChoiceList *list, BgOption *option, int index) {
	//TODO: unique or not? eg, multiple -midi?
	if (index > -1) {
		list->choices = g_list_insert(list->choices, option, index);
	} else {
		list->choices = g_list_append(list->choices, option);
	}
}

static void _bg_option_choice_list_add(gpointer _option, gpointer _list) {
	BgOptionChoiceList *list = (BgOptionChoiceList*) _list;
	BgOption* option = (BgOption*) _option;
	bg_option_choice_list_add(list, option, -1);
}

void bg_option_choice_list_add_all(BgOptionChoiceList *list, BgOptionChoiceList *list_to_add) {
	g_list_foreach(list_to_add->choices, _bg_option_choice_list_add, list);
}

void bg_option_choice_list_remove(BgOptionChoiceList *list, int index) {
	list->choices = g_list_remove(list->choices, bg_option_choide_list_get(list, index));
}

BgOption* bg_option_choide_list_get(BgOptionChoiceList *list, int index) {
	return (BgOption*) g_list_nth_data(list->choices, index);
}

BgOptionList* bg_option_list_new() {
	BgOptionList *list = g_new(BgOptionList, 1);
	list->options = NULL;
	list->table = g_hash_table_new(g_str_hash, g_str_equal);
	return list;
}

void bg_option_list_add(BgOptionList *list, BgOption *option) {
	g_assert(bg_option_list_get(list, option->key) == NULL);
	list->options = g_list_append(list->options, option);
	g_hash_table_insert(list->table, option->key, option);
}

BgOption* bg_option_list_get(BgOptionList *list, const char *key) {
	return g_hash_table_lookup(list->table, key);
}

void bg_option_list_select(BgOptionList *list, const char *key) {
	if (key != NULL) {
		g_assert(bg_option_list_get(list, key) != NULL);
		list->selected = bg_option_list_get(list, key);
	} else {
		list->selected = NULL;
	}
}

static void _bg_command_append_option(gpointer _option, gpointer _command) {
	BgOption *option = (BgOption*) _option;
	BgCommand *command = (BgCommand*) _command;
	command->command = g_strdup_printf("%s %s", command->command, bg_option_commandline(option));
}

BgCommand* bg_command_new(const char *name, BgOptionList *list) {
	BgCommand *command = g_new(BgCommand, 1);
	command->command = g_strdup(name);
	if (list != NULL && g_list_length(list->options) > 0) {
		g_list_foreach(list->options, _bg_command_append_option, command);
	}
	return command;
}
