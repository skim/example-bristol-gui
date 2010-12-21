#include "lgui_common.h"
#include "lgui_config.h"
#include "ltk.h"
#include "string.h"

const char* lgui_name_new(const char *id, const char *widget_type) {
	g_assert(id != NULL && strlen(id) > 0);
	g_assert(widget_type != NULL && strlen(widget_type) > 0);
	return g_strconcat(widget_type, id, NULL);
}

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

void lgui_switch_button_visible_connect(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkButton *button = lgui_builder_get_switch_button(builder, id);
	GtkWidget *box = lgui_builder_get_box(builder, id);
	ltk_switch_visible_connect(button, box);
}

void lgui_switch_check_button_sensitive_connect(GtkBuilder *builder, const char *id) {
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkButton *button = lgui_builder_get_switch_check_button(builder, id);
	GtkWidget *box = lgui_builder_get_box(builder, id);
	ltk_switch_sensitive_connect(button, box);
}
