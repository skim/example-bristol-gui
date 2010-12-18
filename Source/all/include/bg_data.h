#ifndef BG_DATA_H_
#define BG_DATA_H_

#include "lg.h"

typedef struct {
	char *name;
	LgStringHashList *options;
} BgProfile;

typedef struct {
	LgStringHashList *profiles;
	BgProfile *current_profile;
} BgData;

BgProfile* 	bg_profile_new(const char *name);
void 		bg_profile_set_option(BgProfile *profile, LgOption *option);
BgData*		bg_data_new();
void 		bg_data_add_profile(BgData *data, BgProfile *profile);
BgProfile*	bg_data_get_profile(BgData *data, int index);
GList*		bg_data_get_profiles(BgData *data);

#endif /* BG_DATA_H_ */
