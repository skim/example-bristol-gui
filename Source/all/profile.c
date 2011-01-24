#include "profile.h"
#include "ltk_test.h"

LProfile* bg_profile_new() {
	LProfile* profile = l_profile_new();

	l_profile_set_option_value_string(profile, "synth", "mini");

	l_profile_set_option_value_string(profile, "engine", "alsa");
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

void bg_profile_connect(LProfile *profile, GtkBuilder *builder) {
	g_assert(profile != NULL);
	g_assert(builder != NULL);

	GtkComboBox *combo_engine = ltk_builder_get_combo_box(builder, "combo_engine");
	GList *choices_engine = l_profile_get_option_choices(profile, "engine");
	GList *names_engine = l_profile_get_option_choices_names(profile, "engine");
	char *value_engine = l_profile_get_option_value_string(profile, "engine");
	ltk_combo_box_set_cell_renderer_text(combo_engine);
	ltk_combo_box_set_choices_string(combo_engine, names_engine);
	gtk_combo_box_set_active(combo_engine, l_list_index(choices_engine, value_engine, l_string_compare));

	GtkComboBox *combo_samplerate = ltk_builder_get_combo_box(builder, "combo_samplerate");
	GList *choices_samplerate = l_profile_get_option_choices(profile, "samplerate");
	GList *names_samplerate = l_profile_get_option_choices_names(profile, "samplerate");
	LWrapInt *value_samplerate = l_wrap_int(l_profile_get_option_value_int(profile, "samplerate"));
	g_debug("%d", value_samplerate->value);
	ltk_combo_box_set_cell_renderer_text(combo_samplerate);
	ltk_combo_box_set_choices_string(combo_samplerate, names_samplerate);
	gtk_combo_box_set_active(combo_samplerate, l_list_index(choices_samplerate, value_samplerate, l_wrap_int_compare));


}
