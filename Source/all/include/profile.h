#ifndef PROFILE_H_
#define PROFILE_H_

#include <llib.h>
#include <gtk/gtk.h>
#include "bg_session.h"

BgSession*		bg_create_session(GtkBuilder *builder);
LOptionList* 	bg_create_default_profile();
LOptionList*	bg_create_profile(LOptionList *copy_from);

#endif /* PROFILE_H_ */
