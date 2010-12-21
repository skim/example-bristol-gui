#include "l_config.h"
#include "l_common.h"
#include "l_option.h"
#include "bg_config.h"
#include <gtk/gtk.h>

int main(int argc, char **argv) {
	LOptionList *profile = l_option_list_new();
	l_option_list_put_option(profile, l_option_new_string("engine", NULL));
	l_option_list_put_option(profile, l_option_new_int("midichannel", "channel"));
	l_option_list_put_option(profile, l_option_new_string("synth", NULL));

	l_option_list_set_value_string(profile, "engine", "jack");
	l_option_list_set_value_int(profile, "midichannel", 1);
	l_option_list_set_value_string(profile, "synth", "mini");

	g_debug("startBristol %s", l_option_list_render_cli(profile));

	return 0;
}

