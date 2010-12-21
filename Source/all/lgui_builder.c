#include "lgui_builder.h"
#include "lgui_common.h"
#include "lgui_config.h"
#include "ltk.h"
#include <string.h>

GtkButton* lgui_builder_get_switch_button(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	const char *name = lgui_name_new(id, LGUI_PREFIX_SWITCH_BUTTON);
	GtkButton *button = ltk_builder_get_button(builder, name);
	if (button == NULL) {
		g_warning("switch button not found for id: %s and name: %s", id, name);
	}
	return button;
}

GtkButton* lgui_builder_get_switch_check_button(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	const char *name = lgui_name_new(id, LGUI_PREFIX_SWITCH_CHECK_BUTTON);
	GtkButton *button = ltk_builder_get_button(builder, name);
	if (button == NULL) {
		g_warning("switch check button not found for id: %s and name: %s", id, name);
	}
	return button;
}

GtkWidget* lgui_builder_get_box(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	const char *name = lgui_name_new(id, LGUI_PREFIX_BOX);
	GtkWidget *box = ltk_builder_get_widget(builder, name);
	if (box == NULL) {
		g_warning("box not found for id: %s and name: %s", id, name);
	}
	return box;
}

GtkWidget* lgui_builder_get_window(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	const char *name = lgui_name_new(id, LGUI_PREFIX_WINDOW);
	GtkWidget *window = ltk_builder_get_widget(builder, name);
	if (window == NULL) {
		g_warning("window not found for id: %s and name: %s", id, name);
	}
	return window;
}
