#include "bg_starter.h"
#include <glib.h>

void start_bristol() {
	GError **error = g_malloc(sizeof(GError**));
	if (!g_spawn_command_line_async("startBristol -jack -mini -libtest", error)) {
		printf("Could not start bristol: %s", (*error)->message);
	}

}
