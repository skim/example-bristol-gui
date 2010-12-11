#include "bg_options_general.h"

BgOptionChoiceList* bg_engine_choices_new() {
	BgOptionChoiceList *list = bg_option_choice_list_new();
	bg_option_choice_list_add(list, bg_empty_option_new("engine", "JACK", "jack"), -1);
	bg_option_choice_list_add(list, bg_empty_option_new("engine", "ALSA", "alsa"), -1);
	bg_option_choice_list_add(list, bg_empty_option_new("engine", "OSS", "oss"), -1);
	return list;
}

BgOptionChoiceList* bg_synth_choices_new() {
	BgOptionChoiceList *list = bg_option_choice_list_new();
	bg_option_choice_list_add(list, bg_empty_option_new("synth", "Mini", "mini"), -1);
	bg_option_choice_list_add(list, bg_empty_option_new("synth", "Voyager", "explorer"), -1);
	return list;
}

BgOptionChoiceList* bg_general_choices_new() {
	BgOptionChoiceList *list = bg_option_choice_list_new();
	bg_option_choice_list_add(list, bg_int_option_new("channel", "Midi Channel", 1));
	bg_option_choice_list_add(list, bg_int_option_new("rate", "Sample Rate", 44100));
	bg_option_choice_list_add(list, bg_emptry_option_new("mono", "Mono Only", "mono"));
	return list;
}



