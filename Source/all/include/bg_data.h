#ifndef BG_DATA_H_
#define BG_DATA_H_

#include "bg_common_basic.h"
#include <glib.h>


typedef struct {
	char *id;
	char *name;
} BgCategory;

typedef struct {
	char *id;
	char *name;
} BgProfile;

typedef struct {
	char *id;
	char *name;
	char *image_filename;
	BgCategory *category;
	BgProfile *profile;
} BgSynth;

typedef struct {
	GList *categories;
	GList *synths;
	GListProxy *profiles;
} BgStore;


BgStore*			bg_store_new();
BgCategory* 		bg_category_new(BgStore *store, const char *id, const char *name);
BgProfile*			bg_profile_new(BgStore *store, const char *id, const char *name);
BgSynth*			bg_synth_new(BgStore *store, BgCategory *category, const char *id, const char *name, const char *image_filename);

#endif /* BG_DATA_H_ */
