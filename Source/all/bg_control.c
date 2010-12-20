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

static BgControlPayload* bg_control_payload_new(BgSession *session, GtkBuilder *builder, const char *id, GObject *widget) {
	BgControlPayload *payload = g_new(BgControlPayload, 1);
	payload->session = session;
	payload->builder = builder;
	payload->id = g_strdup(id);
	payload->widget = widget;
	return payload;
}

static void bg_set_runtime_preview_label(BgProfile *profile, GtkBuilder *builder) {
	GtkLabel *label_runtime_preview = GTK_LABEL(gtk_builder_get_object(builder, bg_gui_name("runtime_preview", "label")));
	g_assert(label_runtime_preview != NULL);
	gtk_label_set_text(label_runtime_preview, bg_option_list_render(profile->options));
}

static void bg_set_options_label(BgProfile *profile, GtkBuilder *builder) {
	GtkLabel *label_options = GTK_LABEL(gtk_builder_get_object(builder, bg_gui_name("options", "label")));
	g_assert(label_options != NULL);
	int num = bg_profile_count_active_options(profile) - 1; //-1 because synth is always set
	if (num == 0) {
		gtk_label_set_text(label_options, "None");
	} else {
		gtk_label_set_text(label_options, g_strdup_printf("%d", num));
	}
}

static void bg_set_option_from_profile(BgControlPayload *payload) {
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	GtkToggleButton *check = GTK_TOGGLE_BUTTON(gtk_builder_get_object(payload->builder, bg_gui_name(payload->id, "check")));
	GObject *widget_option = G_OBJECT(gtk_builder_get_object(payload->builder, bg_gui_name(payload->id, option->config->widget_type)));
	g_assert(check != NULL);
	g_assert(widget_option != NULL);
	g_assert(option != NULL);
	gtk_toggle_button_set_active(check, option->active);
	GType type = G_OBJECT_TYPE(payload->widget);
	if (type == GTK_TYPE_COMBO_BOX) {
		bg_combo_box_set_active_value(payload->builder, payload->id, option->value_string);
		g_debug("from profile %s: found %s with %s", profile->name, option->id, option->value_string);
	} else if (type == GTK_TYPE_ADJUSTMENT) {
		gtk_adjustment_set_value(GTK_ADJUSTMENT(payload->widget), option->value_int);
	}
}

static void bg_set_profile(BgSession *session, GtkBuilder *builder) {
	GtkComboBox *combo_profile = GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name("profile", "combo")));
	gtk_combo_box_set_active(combo_profile, session->index_profile);
	BgProfile *profile = bg_session_get_active_profile(session);
	GtkLabel *label_profile = GTK_LABEL(gtk_builder_get_object(builder, bg_gui_name("profile", "label")));
	gtk_label_set_text(label_profile, profile->name);
	int i;
	for (i = 0; i < bg_option_list_length(profile->options); i++) {
		BgOption *option = bg_option_list_get_nth(profile->options, i);
		if (!g_str_equal("special", option->config->widget_type)) {
			GObject *widget = gtk_builder_get_object(builder, bg_gui_name(option->id, option->config->widget_type));
			bg_set_option_from_profile(bg_control_payload_new(session, builder, option->id, widget));
		}
	}
}

static void bg_option_switch_check_button_toggled(GtkCheckButton *check, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check))) {
		if (option == NULL) {
			bg_profile_add_option(profile, bg_control_get_option_from_widget(payload->builder, payload->id, payload->widget));
		} else {
			option->active = TRUE;
		}
		g_debug("on profile %s: activated option %s", profile->name, payload->id);
	} else {
		if (option != NULL) {
			option->active = FALSE;
		} else {
			g_debug("deactivating a non existent option: %s", payload->id);
		}
		g_debug("on profile %s: deactivated option %s", profile->name, payload->id);
	}
	bg_set_options_label(profile, payload->builder);
	bg_set_runtime_preview_label(profile, payload->builder);
}

static void bg_option_combo_box_changed(GtkComboBox *combo, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	g_assert(option != NULL);
	option->value_string = g_strdup(bg_combo_box_get_active_value(payload->builder, payload->id));
	bg_set_runtime_preview_label(profile, payload->builder);
	//g_debug("on profile %s: set %s to %s", profile->name, option->id, option->value_string);
}

static void bg_option_adjustment_changed(GtkAdjustment *adjust, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	BgOption *option = bg_profile_get_option(profile, payload->id);
	g_assert(option != NULL);
	option->value_int = gtk_adjustment_get_value(adjust);
	bg_set_runtime_preview_label(profile, payload->builder);
	//g_debug("on profile %s: set %s to %d", profile->name, option->id, option->value_int);
}

static void bg_profile_combo_box_changed(GtkComboBox *combo, gpointer data) {
	BgControlPayload *payload = (BgControlPayload*) data;
	BgProfile *profile = bg_session_get_active_profile(payload->session);
	payload->session->index_profile = gtk_combo_box_get_active(combo);
	//deactivate all
	int i;
	for (i = 0; i < bg_option_list_config_length(profile->options); i++) {
		BgOptionConfig *config = bg_option_list_get_nth_config(profile->options, i);
		if (!g_str_equal("special", config->widget_type)) {
			GtkToggleButton *check = GTK_TOGGLE_BUTTON(gtk_builder_get_object(payload->builder, bg_gui_name(config->id, "check")));
			if (gtk_toggle_button_get_active(check)) {
				gtk_toggle_button_set_active(check, FALSE);
			}
		}
	}

	bg_set_profile(payload->session, payload->builder);
}

BgOption* bg_control_get_option_from_widget(GtkBuilder *builder, const char *id, GObject *widget) {
	g_assert(widget != NULL);
	GType type = G_OBJECT_TYPE(widget);
	if (type == GTK_TYPE_COMBO_BOX) {
		return bg_option_new_string(id, bg_combo_box_get_active_value(builder, id));
	} else if (type == GTK_TYPE_ADJUSTMENT) {
		return bg_option_new_int(id, gtk_adjustment_get_value(GTK_ADJUSTMENT(widget)));
	} else {
		g_warning("could not get option for %s from widget", id);
	}
	return NULL;
}

void bg_set_signals_from_profile(BgControlPayload *payload) {
	GType type = G_OBJECT_TYPE(payload->widget);
	if (type == GTK_TYPE_COMBO_BOX) {
		g_signal_connect(payload->widget, "changed", G_CALLBACK(bg_option_combo_box_changed), payload);
	} else if (type == GTK_TYPE_ADJUSTMENT) {
		g_signal_connect(payload->widget, "value-changed", G_CALLBACK(bg_option_adjustment_changed), payload);
	}
}

void bg_control_init(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget) {
	g_debug("initializing control for %s, widget type: %s", id, option_widget);
}

void bg_control_connect(BgSession *session, GtkBuilder *builder, const char *id, const char *option_widget) {
	GtkToggleButton *check = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "check")));
	GObject *widget_option = G_OBJECT(gtk_builder_get_object(builder, bg_gui_name(id, option_widget)));
	g_assert(check != NULL);
	g_assert(widget_option != NULL);
	g_debug("connection control for %s, type: %s", id, option_widget);
	BgControlPayload *payload = bg_control_payload_new(session, builder, id, widget_option);
	bg_set_signals_from_profile(payload);
	g_signal_connect(check, "toggled", G_CALLBACK(bg_option_switch_check_button_toggled), bg_control_payload_new(session, builder, id, G_OBJECT(widget_option)));
}

void bg_control_before_start(BgSession *session, GtkBuilder *builder) {
	BgProfile *profile = bg_session_get_active_profile(session);
	int i;
	for (i = 0; i < bg_option_list_config_length(profile->options); i++) {
		BgOptionConfig *config = bg_option_list_get_nth_config(profile->options, i);
		if (!g_str_equal("special", config->widget_type)) {
			bg_control_init(session, builder, config->id, config->widget_type);
			bg_control_connect(session, builder, config->id, config->widget_type);
		}
	}
	bg_set_profile(session, builder);
	GtkComboBox *combo_profile = GTK_COMBO_BOX(gtk_builder_get_object(builder, bg_gui_name("profile", "combo")));
	g_signal_connect(combo_profile, "changed", G_CALLBACK(bg_profile_combo_box_changed), bg_control_payload_new(session, builder, "profile", G_OBJECT(combo_profile)));
	bg_set_options_label(profile, builder);
	bg_set_runtime_preview_label(profile, builder);
}
