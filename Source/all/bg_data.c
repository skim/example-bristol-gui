#include "bg_data.h"

typedef struct {
	char *id;
} bg_id;

static int bg_list_compare_id(gconstpointer a, gconstpointer b) {
	bg_id *id_a = (bg_id*)a;
	bg_id *id_b = (bg_id*)b;
	return g_strcmp0(id_a->id, id_b->id);
}

bg_store* bg_store_new() {
	bg_store *store = g_new(bg_store, 1);
	store->categories = NULL;
	store->synths = NULL;
	store->synth_params = NULL;
	return store;
}

bg_category* bg_category_new(bg_store *store, const char *id, const char *name) {
	bg_category *category = g_new(bg_category, 1);
	category->id = g_strdup(id);
	category->name = g_strdup(name);
	g_assert(g_list_find_custom(store->categories, category, bg_list_compare_id) == NULL);
	store->categories = g_list_append(store->categories, category);
	return category;
}

bg_synth_params* bg_synth_params_new(bg_store *store, const char *id, const char *name) {
	bg_synth_params *params = g_new(bg_synth_params, 1);
	params->id = g_strdup(id);
	params->name = g_strdup(name);
	g_assert(g_list_find_custom(store->synth_params, params, bg_list_compare_id) == NULL);
	store->synth_params = g_list_append(store->synth_params, params);
	return params;
}

bg_synth* bg_synth_new(bg_store *store, bg_category *category, const char *id, const char *name) {
	bg_synth *synth = g_new(bg_synth, 1);
	synth->id = g_strdup(id);
	synth->name = g_strdup(name);
	synth->category = category;
	g_assert(g_list_find_custom(store->synths, synth, bg_list_compare_id) == NULL);
	store->synths= g_list_append(store->synths, synth);
	return synth;
}

