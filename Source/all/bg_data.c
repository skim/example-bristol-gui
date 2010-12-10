#include "bg_data.h"
#include "bg_config.h"

typedef struct {
	char *id;
	char *name;
} bg_id;

static int bg_list_compare_id(gconstpointer a, gconstpointer b) {
	bg_id *id_a = (bg_id*) a;
	bg_id *id_b = (bg_id*) b;
	return g_strcmp0(id_a->id, id_b->id);
}


BgStore* bg_store_new() {
	BgStore *store = g_new(BgStore, 1);
	store->categories = NULL;
	store->synths = NULL;
	store->profiles = g_list_proxy_new();
	bg_profile_new(store, BG_PROFILE_DEFAULT_ID, BG_PROFILE_DEFAULT_NAME);
	return store;
}

BgCategory* bg_category_new(BgStore *store, const char *id, const char *name) {
	BgCategory *category = g_new(BgCategory, 1);
	category->id = g_strdup(id);
	category->name = g_strdup(name);
	g_assert(g_list_find_custom(store->categories, category, bg_list_compare_id) == NULL);
	store->categories = g_list_append(store->categories, category);
	return category;
}

BgProfile* bg_profile_new(BgStore *store, const char *id, const char *name) {
	BgProfile *params = g_new(BgProfile, 1);
	params->id = g_strdup(id);
	params->name = g_strdup(name);
	g_assert(g_list_find_custom(store->profiles->list, params, bg_list_compare_id) == NULL);
	store->profiles->list = g_list_append(store->profiles->list, params);
	return params;
}

BgSynth* bg_synth_new(BgStore *store, BgCategory *category, const char *id, const char *name, const char *image_filename) {
	BgSynth *synth = g_new(BgSynth, 1);
	synth->id = g_strdup(id);
	synth->name = g_strdup(name);
	synth->category = category;
	if (image_filename != NULL) {
		synth->image_filename = g_strdup(image_filename);
	}
	synth->profile = (BgProfile*) g_list_first(store->profiles->list);
	g_assert(g_list_find_custom(store->synths, synth, bg_list_compare_id) == NULL);
	store->synths = g_list_append(store->synths, synth);
	return synth;
}
