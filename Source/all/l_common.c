#include "l_common.h"
#include "l_config.h"
#include "glib.h"

char* l_data_path_new(const char *filename) {
	g_assert(filename != NULL);
	return g_strdup_printf("%s/%s", L_DATA_PATH, filename);
}
