#include "ltk_common.h"
#include "string.h"

LtkPayload* ltk_payload_new(LOptionList *options, const char *id) {
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	LtkPayload *payload = g_new(LtkPayload, 1);
	payload->options = options;
	payload->id = g_strdup(id);
	return payload;
}

void ltk_object_mark(GtkObject *object) {
	g_assert(object != NULL);
	g_object_set_data(G_OBJECT(object), LTK_OBJECT_MARK_KEY, GINT_TO_POINTER(1));
}

gboolean ltk_object_is_marked(GtkObject *object) {
	g_assert(object != NULL);
	return g_object_get_data(G_OBJECT(object), LTK_OBJECT_MARK_KEY) != NULL;
}

void ltk_button_set_stock_image(GtkButton *button, const char *stock_name, GtkIconSize size) {
	g_assert(button != NULL);
	g_assert(stock_name != NULL && strlen(stock_name) > 0);
	gtk_button_set_image(button, gtk_image_new_from_stock(stock_name, size));
}

void ltk_toggle_button_set_active_from_option(GtkToggleButton *toggle, LOptionList *options, const char *id) {
	g_assert(toggle != NULL);
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	if (l_option_list_get_value(options, id) != NULL) {
		gtk_toggle_button_set_active(toggle, l_value_is_enabled(l_option_list_get_value(options, id)));
	}
}

static void ltk_toggle_button_clicked(GtkToggleButton *toggle, gpointer data) {
	LtkPayload *payload = (LtkPayload*) data;
	if (l_option_list_get_value(payload->options, payload->id) != NULL) {
		l_value_set_enabled(l_option_list_get_value(payload->options, payload->id), gtk_toggle_button_get_active(toggle));
	} else {
		g_warning("option: %s enabled but not set", payload->id);
	}
	g_debug("%s", l_option_list_render_cli(payload->options));
}

void ltk_toggle_button_connect_option(GtkToggleButton *toggle, LOptionList *options, const char *id) {
	g_assert(toggle != NULL);
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	ltk_toggle_button_set_active_from_option(toggle, options, id);
	g_signal_connect(toggle, "clicked", G_CALLBACK(ltk_toggle_button_clicked), ltk_payload_new(options, id));
}
