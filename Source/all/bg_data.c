#include "bg_data.h"

bg_config* bg_config_new(bg_synth *synth, const char *name) {
	bg_config *config = g_new(bg_config, 1);
	config->synth = synth;
	config->name = g_strdup(name);
	config->identifier = g_strdup("bristol");
	config->midichannel = 1;
	config->periodsize = 256;
	config->samplerate = 44100;
	config->soundengine = BG_JACK;
	return config;
}

bg_store* bg_store_new() {
	bg_store *store = g_new(bg_store, 1);
	store->companies = g_hash_table_new(g_str_hash, g_str_equal);
	return store;
}

bg_company* bg_company_new(bg_store *store, const char *id, const char *name) {
	g_assert(store != NULL);
	bg_company *company = g_hash_table_lookup(store->companies, id);
	if (company != NULL) {
		g_warning("bg_company with id %s already exists", id);
	} else {
		company = g_new(bg_company, 1);
		company->store = store;
		company->id = g_strdup(id);
		company->name = g_strdup(name);
		company->synths = g_hash_table_new(g_str_hash, g_str_equal);
		g_hash_table_insert(store->companies, g_strdup(id), company);
	}
	return company;
}

bg_synth* bg_synth_new(bg_company *company, const char *id, const char *name, const char *image_filename) {
	bg_synth *synth = g_hash_table_lookup(company->synths, id);
	if (synth != NULL) {
		g_warning("bg_synth with id %s already exists", id);
	} else {
		synth = g_new(bg_synth, 1);
		synth->company = company;
		synth->id = g_strdup(id);
		synth->name = g_strdup(name);
		synth->image_filename = g_strdup(image_filename);
		synth->configs = g_hash_table_new(g_str_hash, g_str_equal);
		g_hash_table_insert(company->synths, g_strdup(id), synth);
	}
	return synth;
}
