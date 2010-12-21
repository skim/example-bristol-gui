#include "lgui_switch.h"
#include "lgui_builder.h"
#include "ltk.h"
#include <string.h>

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
