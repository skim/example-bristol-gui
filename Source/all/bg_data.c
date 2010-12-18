#include "bg_data.h"
#include "string.h"

BgProfile* bg_profile_new(const char *name) {
	g_assert(name != NULL);
	g_assert(strlen(name) > 1);
	BgProfile *profile = g_new(BgProfile, 1);
	profile->name = g_strdup(name);
	profile->options = lg_hash_list_new();
	return profile;
}

void bg_profile_set_option(BgProfile *profile, LgOption *option) {
	g_assert(profile != NULL);
	g_assert(option != NULL);
	g_assert(option->category != NULL);
}

BgData* bg_data_new() {
	BgData *data = g_new(BgData, 1);
	data->profiles = lg_hash_list_new();
	BgProfile *profile = bg_profile_new("Default");
	bg_data_add_profile(data, profile);
	return data;
}

void bg_data_add_profile(BgData *data, BgProfile *profile) {
	g_assert(data != NULL);
	g_assert(profile != NULL);
	lg_hash_list_add(data->profiles, profile->name, profile);
}

GList* bg_data_get_profiles(BgData *data) {
	return data->profiles->list;
}

BgProfile*	bg_data_get_profile(BgData *data, int index) {
	return (BgProfile*) g_list_nth_data(bg_data_get_profiles(data), index);
}
