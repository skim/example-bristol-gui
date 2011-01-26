#include "profile.h"
#include "ltk_test.h"
#include <string.h>

LProfile* bg_profile_new() {
	LProfile* profile = l_profile_new();

	l_profile_set_option_value_string(profile, "synth", "mini");

	l_profile_set_option_value_string(profile, "engine", "alsa");
	l_profile_set_option_enabled(profile, "engine", TRUE);
	l_profile_add_named_option_choice_string(profile, "engine", "alsa", "ALSA");
	l_profile_add_named_option_choice_string(profile, "engine", "jack", "JACK");
	l_profile_add_named_option_choice_string(profile, "engine", "oss", "OSS");

	l_profile_set_option_value_int(profile, "samplerate", 48000);
	l_profile_add_named_option_choice_int(profile, "samplerate", 11025, "11,025 - low MPEG");
	l_profile_add_named_option_choice_int(profile, "samplerate", 22050, "22,025 - mid MPEG");
	l_profile_add_named_option_choice_int(profile, "samplerate", 44100, "44.100 - CD-Audio, MPEG-1");
	l_profile_add_named_option_choice_int(profile, "samplerate", 48000, "48,000 - HiFi Standard");
	l_profile_add_named_option_choice_int(profile, "samplerate", 96000, "96,000 - DVD-Audio");

	return profile;
}

static void bg_profile_connect_toggle_enable(LProfile *profile, GtkBuilder *builder, const char *id) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkToggleButton *toggle = ltk_builder_get_toggle_button(builder, l_strdup_printf("check_%s", id));
	g_assert(toggle != NULL);
	ltk_toggle_button_connect_option_enabled(toggle, profile, id);
}

static void bg_profile_disconnect_toggle_enable(LProfile *profile, GtkBuilder *builder, const char *id) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkToggleButton *toggle = ltk_builder_get_toggle_button(builder, l_strdup_printf("check_%s", id));
	g_assert(toggle != NULL);
	ltk_toggle_button_disconnect_option_enabled(toggle, profile, id);
}


static void bg_profile_connect_combo_box(LProfile *profile, GtkBuilder *builder, const char *id) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, l_strdup_printf("combo_%s", id));
	GList *names = l_profile_get_option_choices_names(profile, id);
	GList *choices = l_profile_get_option_choices(profile, id);
	g_assert(combo != NULL);
	g_assert(names != NULL);
	g_assert(choices != NULL);
	ltk_combo_box_set_choices(combo, choices, names);
}

static void bg_profile_combo_box_set_value_string(LProfile *profile, GtkBuilder *builder, const char *id) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, l_strdup_printf("combo_%s", id));
	g_assert(combo != NULL);
	char *value = l_profile_get_option_value_string(profile, id);
	ltk_combo_box_set_active_string(combo, value);
}

static void bg_profile_combo_box_set_value_int(LProfile *profile, GtkBuilder *builder, const char *id) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	GtkComboBox *combo = ltk_builder_get_combo_box(builder, l_strdup_printf("combo_%s", id));
	int value = l_profile_get_option_value_int(profile, id);
	ltk_combo_box_set_active_int(combo, value);
}

void bg_profile_connect(LProfile *profile, GtkBuilder *builder) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);

	bg_profile_connect_toggle_enable(profile, builder, "synth");

	bg_profile_connect_combo_box(profile, builder, "engine");
	bg_profile_connect_toggle_enable(profile, builder, "engine");
	bg_profile_combo_box_set_value_string(profile, builder, "engine");

	bg_profile_connect_combo_box(profile, builder, "samplerate");
	bg_profile_connect_toggle_enable(profile, builder, "samplerate");
	bg_profile_combo_box_set_value_int(profile, builder, "samplerate");
}

void bg_profile_disconnect(LProfile *profile, GtkBuilder *builder) {
	bg_profile_disconnect_toggle_enable(profile, builder, "synth");
	bg_profile_disconnect_toggle_enable(profile, builder, "engine");
	bg_profile_disconnect_toggle_enable(profile, builder, "samplerate");
}
