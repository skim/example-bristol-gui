#include "app_profile.h"

LOptionList* app_profile_new() {

	LOption *option_synth = l_option_new_string("synth", FALSE);

	LOption *option_engine = l_option_new_string("engine", FALSE);
	LValueList *choices_engine = l_value_list_new_string();
	l_value_list_put_value(choices_engine, "JACK", l_value_new_string("jack"));
	l_value_list_put_value(choices_engine, "ALSA", l_value_new_string("alsa"));
	l_option_set_choices(option_engine, choices_engine);

	LOption *option_samplerate = l_option_new_int("samplerate", "rate");
	LValueList *choices_samplerate = l_value_list_new_int();
	l_value_list_put_value(choices_samplerate, "22,050hz", l_value_new_int(22050));
	l_value_list_put_value(choices_samplerate, "44,050hz", l_value_new_int(44000));
	l_value_list_put_value(choices_samplerate, "48,000hz", l_value_new_int(48000));
	l_option_set_choices(option_samplerate, choices_samplerate);

	LOption *option_midichannel = l_option_new_int("midichannel", "channel");

	LOptionList *profile = l_option_list_new();
	l_option_list_insert_option(profile, option_synth, l_value_new_string("mini"));
	l_option_list_insert_option(profile, option_engine, l_value_new_string("alsa"));
	l_option_list_insert_option(profile, option_midichannel, l_value_new_int(1));
	l_option_list_insert_option(profile, option_samplerate, l_value_new_int(48000));

	return profile;
}

void app_profile_prepare_session(BgSession *session) {
	g_assert(session != NULL);
	bg_session_register_combo_box(session, "engine", "combo_engine");
	bg_session_register_enable_button(session, "engine", "check_engine", NULL);
	bg_session_register_combo_box(session, "samplerate", "combo_samplerate");
	bg_session_register_enable_button(session, "samplerate", "check_samplerate", NULL);
	bg_session_register_adjustment(session, "midichannel", "adjust_midichannel");
	bg_session_register_enable_button(session, "midichannel", "check_midichannel", "box_midichannel");
}
