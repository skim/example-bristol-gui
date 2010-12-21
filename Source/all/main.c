#include "bg_config.h"
#include "llib.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	LOptionList *profile = l_option_list_new();
	l_option_list_put_option(profile, l_option_new_string("engine", NULL));
	l_option_list_put_option(profile, l_option_new_int("midichannel", "channel"));
	l_option_list_put_option(profile, l_option_new_string("synth", NULL));

	LValue *test = l_value_new_string("Test");
	l_option_list_set_value(profile, "synth", test);
	l_option_list_set_value(profile, "engine", test);
	g_debug("startBristol %s", l_option_list_render_cli(profile));
	g_debug("startBristol %s", l_option_list_render_cli(profile));

	return 0;
}

