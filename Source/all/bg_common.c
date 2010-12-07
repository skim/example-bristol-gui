#include "bg_common.h"
#include "bg_config.h"
#include "glib.h"

char* bg_path_new(const char *filename) {
	return g_strconcat(BG_PATH_DATA, "/", filename, NULL);
}
