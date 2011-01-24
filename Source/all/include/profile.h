#ifndef PROFILE_H_
#define PROFILE_H_

#include <lgui.h>

LProfile* 	bg_profile_new();
void		bg_profile_connect(LProfile *profile, GtkBuilder *builder);

#endif /* PROFILE_H_ */
