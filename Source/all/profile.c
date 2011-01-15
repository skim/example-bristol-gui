#include "profile.h"

BgSession* bg_create_session(GtkBuilder *builder) {
	g_assert(builder != NULL);
	LValueList *engines = l_value_list_new_string();
	l_value_list_put_value(engines, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(engines, "ALSA", l_value_new_string("alsa"));
	l_value_list_put_value(engines, "OSS", l_value_new_string("oss"));
	l_value_list_put_value(engines, "DebugLongString", l_value_new_string("averylongstringtochecklinewrapping"));


	LValueList *samplerates = l_value_list_new_int();
	l_value_list_put_value(samplerates, "11,025 Hz - (1/4 Audio CD)", l_value_new_int(11025));
	l_value_list_put_value(samplerates, "22,050 Hz - (1/2 Audio CD)", l_value_new_int(22050));
	l_value_list_put_value(samplerates, "44,100 Hz - (Audio CD)", l_value_new_int(44100));
	l_value_list_put_value(samplerates, "48,000 Hz - (HiFi/ Video Standard)", l_value_new_int(48000));
	l_value_list_put_value(samplerates, "96,000 Hz - (DVD Audio)", l_value_new_int(96000));

	BgSession *session = bg_session_new(builder);

	bg_session_register_enable_button(session, "synth", "check_synth", "box_synth");

	bg_session_register_combo_box(session, "engine", "combo_engine", engines);
	bg_session_register_enable_button(session, "engine", "check_engine", NULL);

	bg_session_register_adjustment(session, "midichannel", "adjust_midichannel");
	bg_session_register_enable_button(session, "midichannel", "check_midichannel", "box_midichannel");

	bg_session_register_combo_box(session, "samplerate", "combo_samplerate", samplerates);
	bg_session_register_enable_button(session, "samplerate", "check_samplerate", NULL);

	return session;
}

LOptionList* bg_create_default_profile() {
	LOptionList *profile = l_option_list_new();

	LValue *value_synth = l_value_new_string("mini");
	l_value_set_enabled(value_synth, TRUE);
	LValue *value_engine = l_value_new_string("jack");
	LValue *value_samplerate = l_value_new_int(48000);
	LValue *value_midichannel = l_value_new_int(1);

	l_option_list_insert_option(profile, l_option_new_string("synth", FALSE), value_synth);
	l_option_list_insert_option(profile, l_option_new_string("engine", NULL), value_engine);
	l_option_list_insert_option(profile, l_option_new_int("midichannel", "channel"), value_midichannel);
	l_option_list_insert_option(profile, l_option_new_int("samplerate", "rate"), value_samplerate);

	return profile;
}

LOptionList* bg_create_profile(LOptionList *copy_from) {
	g_assert(copy_from != NULL);
	LOptionList *profile = l_option_list_new();
	int i;
	for (i = 0; i < l_option_list_length_options(copy_from); i++) {
		LOption *option = l_option_list_nth_option(copy_from, i);
		LValue *copy_from_value = l_option_list_get_value(copy_from, l_option_get_id(option));
		g_assert(copy_from_value != NULL);
		LValue *value = l_value_new_from_value(copy_from_value);
		l_option_list_insert_option(profile, l_option_new_from_option(option), value);
	}
	return profile;
}
