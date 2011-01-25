#include "gui.h"
#include <lgui.h>
#include <string.h>

static void bg_connect_switch_visible(GtkBuilder *builder, const char *base) {
	g_assert(builder != NULL);
	g_assert(base != NULL && strlen(base) > 0);
	ltk_button_connect_visible_switch(ltk_builder_get_button(builder, l_strdup_printf("switch_%s", base)), ltk_builder_get_widget(builder, l_strdup_printf("box_%s", base)));
}

static void bg_connect_switch_sensitive(GtkBuilder *builder, const char *base) {
	g_assert(builder != NULL);
	g_assert(base != NULL && strlen(base) > 0);
	ltk_button_connect_sensitive_switch(ltk_builder_get_button(builder, l_strdup_printf("check_%s", base)), ltk_builder_get_widget(builder, l_strdup_printf("box_%s", base)));
}

static void bg_connect_combo_box(GtkBuilder *builder, const char *base) {
	g_assert(builder != NULL);
	g_assert(base != NULL && strlen(base) > 0);
	ltk_combo_box_set_cell_renderer_text(ltk_builder_get_combo_box(builder, l_strdup_printf("combo_%s", base)));
}

void bg_gui_connect(GtkBuilder *builder) {
	g_assert(builder != NULL);

	bg_connect_switch_visible(builder, "profile");
	bg_connect_switch_visible(builder, "synth");
	bg_connect_switch_visible(builder, "options");
	bg_connect_switch_visible(builder, "command");
	bg_connect_switch_visible(builder, "runtimes");

	bg_connect_switch_sensitive(builder, "synth");
	bg_connect_switch_sensitive(builder, "engine");
	bg_connect_combo_box(builder, "engine");
	bg_connect_switch_sensitive(builder, "midichannel");
	bg_connect_switch_sensitive(builder, "samplerate");
	bg_connect_combo_box(builder, "samplerate");

}
