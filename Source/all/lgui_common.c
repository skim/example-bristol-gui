#include "lgui_common.h"
#include "lgui_config.h"
#include "ltk.h"
#include "string.h"

const char* lgui_name_new(const char *id, const char *widget_type) {
	g_assert(id != NULL && strlen(id) > 0);
	g_assert(widget_type != NULL && strlen(widget_type) > 0);
	return g_strconcat(widget_type, id, NULL);
}
