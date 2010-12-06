#include "bg_configuration.h"
#include <glib.h>

bg_configuration* bg_configuration_new(const char *name) {
	bg_configuration *config = g_new(bg_configuration, 1);
	config->name = g_strdup(name);
	config->identifier = g_strdup("bristol");
	config->midichannel = 1;
	config->periodsize = 256;
	config->samplerate = 44100;
	config->soundengine = BG_JACK;
	return config;
}
