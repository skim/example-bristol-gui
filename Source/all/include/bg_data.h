#ifndef BG_DATA_H_
#define BG_DATA_H_

#include <glib.h>

typedef enum {
	BG_JACK,
	BG_ALSA,
	BG_PULSE,
	BG_OSS
} BG_SOUNDENGINE;

typedef struct {
	GHashTable *companies;
} bg_store;

typedef struct {
	bg_store *store;
	char *id;
	char *name;
	GHashTable *synths;
	unsigned int tab_index;
} bg_company;

typedef struct {
	bg_company *company;
	char *id;
	char *name;
	char *image_filename;
	GHashTable *configs;
	unsigned int tab_index;
} bg_synth;

typedef struct {
	bg_synth *synth;
	char *id;
	char *name;
	BG_SOUNDENGINE soundengine;
	char *identifier;
	unsigned int samplerate;
	unsigned int periodsize;
	unsigned int midichannel;
} bg_config;


bg_store*	bg_store_new();
bg_company* bg_company_new(bg_store *store, const char *id, const char *name);
bg_synth* 	bg_synth_new(bg_company *company, const char *id, const char *name, const char *image_filename);
bg_config* 	bg_config_new(bg_synth *synth, const char *name);


#endif /* BG_DATA_H_ */
