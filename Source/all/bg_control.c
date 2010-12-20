#include "bg_control.h"
#include "bg_session.h"
#include "bg_gui.h"
#include <gtk/gtk.h>

typedef struct {
	BgSession *session;
	GtkBuilder *builder;
	char *id;
	GObject *widget;
} BgControlPayload;

static void bg_set_options_label(BgProfile *profile, GtkBuilder *builder) {
	GtkLabel *label_options = GTK_LABEL(gtk_builder_get_object(builder, bg_gui_name("options", "label")));
	int num = bg_profile_count_options(profile);
	if (num == 0) {
		gtk_label_set_text(label_options, "None");
	} else {
		gtk_label_set_text(label_options, g_strdup_printf("%d", num));
	}

}

static void bg_option_switch_check_button_toggled(GtkCheckButton *check, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check))) {
		bg_profile_add_option(profile, bg_get_option_from_widget(payload->builder, payload->id, payload->widget));
		g_debug("on profile %s: added option %s", profile->name, payload->id);
	} else {
		bg_profile_remove_option(profile, payload->id);
		g_debug("on profile %s: removed option %s", profile->name, payload->id);
	}
	bg_set_options_label(profile, payload->builder);
}

static void bg_option_combo_box_changed(GtkComboBox *combo, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	g_assert(option != NULL);
	option->value_string = g_strdup(bg_combo_box_get_active_value(payload->builder, payload->id));
	//g_debug("on profile %s: set %s to %s", profile->name, option->id, option->value_string);
}

static void bg_option_adjustment_changed(GtkAdjustment *adjust, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	g_assert(option != NULL);
	option->value_int = gtk_adjustment_get_value(adjust);
	//g_debug("on profile %s: set %s to %d", profile->name, option->id, option->value_int);
}

BgOption* bg_get_option_from_widget(GtkBuilder *builder, const char *id, GObject *widget) {
	g_assert(widget != NULL);
	GType type = G_OBJECT_TYPE(widget);
	if (type == GTK_TYPE_COMBO_BOX) {
		return bg_option_new_string(id, FALSE, bg_combo_box_get_active_value(builder, id));
	} else if (type == GTK_TYPE_ADJUSTMENT) {
		return bg_option_new_int(id, TRUE, gtk_adjustment_get_value(GTK_ADJUSTMENT(widget)));
	} else {
		g_warning("could not get option for %s from widget", id);
	}
	return NULL;
}

void bg_set_option_from_profile(BgControlPayload *payload) {
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	if (option != NULL) {
		GType type = G_OBJECT_TYPE(payload->widget);
		if (type == GTK_TYPE_COMBO_BOX) {
			bg_combo_box_set_active_value(payload->builder, payload->id, option->value_string);
			g_debug("from profile %s: found %s with %s", profile->name, option->id, option->value_string);
		} else if (type == GTK_TYPE_ADJUSTMENT) {
			gtk_adjustment_set_value(GTK_ADJUSTMENT(payload->widget), option->value_int);
		}
	}
}

void bg_set_signals_from_profile(BgControlPayload *payload) {
	GType type = G_OBJECT_TYPE(payload->widget);
	if (type == GTK_TYPE_COMBO_BOX) {
		g_signal_connect(payload->widget, "changed", G_CALLBACK(bg_option_combo_box_changed), payload);
	} else if (type == GTK_TYPE_ADJUSTMENT) {
		g_signal_connect(payload->widget, "value-changed", G_CALLBACK(bg_option_adjustment_changed), payload);
	}
}

BgControlPayload* bg_control_payload_new(BgSession *session, GtkBuilder *builder, const char *id, GObject *widget) {
	BgControlPayload *payload = g_new(BgControlPayload, 1);
	payload->session = session;
	payload->builder = builder;
	payload->id = g_strdup(id);
	payload->widget = widget;
	return payload;
}

void bg_option_init(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget) {
	GtkToggleButton *check = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "check")));
	GObject *widget_option = G_OBJECT(gtk_builder_get_object(builder, bg_gui_name(id, option_widget)));
	BgProfile *profile = bg_session_get_active_profile(session);
	g_assert(check != NULL);
	g_assert(widget_option != NULL);
	g_debug("on profile %s: initializing control for %s, type: %s", profile->name, id, option_widget);
	BgControlPayload *payload = bg_control_payload_new(session, builder, id, widget_option);
	bg_set_option_from_profile(payload);
	gtk_toggle_button_set_active(check, bg_profile_get_option(profile, id) != NULL);
}

void bg_option_connect(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget) {
	GtkToggleButton *check = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "check")));
	GObject *widget_option = G_OBJECT(gtk_builder_get_object(builder, bg_gui_name(id, option_widget)));
	BgProfile *profile = bg_session_get_active_profile(session);
	g_assert(check != NULL);
	g_assert(widget_option != NULL);
	g_debug("on profile %s: connection control for %s, type: %s", profile->name, id, option_widget);
	BgControlPayload *payload = bg_control_payload_new(session, builder, id, widget_option);
	bg_set_signals_from_profile(payload);
	g_signal_connect(check, "toggled", G_CALLBACK(bg_option_switch_check_button_toggled), bg_control_payload_new(session, builder, id, G_OBJECT(widget_option)));
}

void bg_options_before_start(BgSession *session, GtkBuilder *builder) {
	BgProfile *profile = bg_session_get_active_profile(session);
	bg_set_options_label(profile, builder);
}
