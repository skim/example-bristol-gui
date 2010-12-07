#ifndef BG_DATA_H_
#define BG_DATA_H_

#include <glib.h>


typedef struct {
	char *id;
	char *name;
} bg_category;

typedef struct {
	char *id;
	char *name;
} bg_synth_params;

typedef struct {
	char *id;
	char *name;
	bg_category *category;
	GList *params;
} bg_synth;

typedef struct {
	GList *categories;
	GList *synths;
	GList *synth_params;
} bg_store;

bg_store*			bg_store_new();
bg_category* 		bg_category_new(bg_store *store, const char *id, const char *name);
bg_synth_params*	bg_synth_params_new(bg_store *store, const char *id, const char *name);
bg_synth*			bg_synth_new(bg_store *store, bg_category *category, const char *id, const char *name);

#endif /* BG_DATA_H_ */
