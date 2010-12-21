#include "ltk_builder.h"
#include "string.h"
#include "llib.h"

GtkBuilder* ltk_builder_new_from_data_path(const char *filename) {
	g_assert(filename != NULL && strlen(filename) > 0);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;
	if (!gtk_builder_add_from_file(builder, l_data_path_new(filename), &error)) {
		g_warning("%s", error->message);
	} else {
		return builder;
	}
	return NULL;
}

GtkWidget* ltk_builder_get_widget(GtkBuilder *builder, const char *name) {
	g_assert(builder != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	return GTK_WIDGET(gtk_builder_get_object(builder, name));
}

GtkButton* ltk_builder_get_button(GtkBuilder *builder, const char *name) {
	g_assert(builder != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	return GTK_BUTTON(ltk_builder_get_widget(builder, name));
}

GtkComboBox* ltk_builder_get_combo_box(GtkBuilder *builder, const char *name) {
	g_assert(builder != NULL);
	g_assert(name != NULL && strlen(name) > 0);
	return GTK_COMBO_BOX(ltk_builder_get_widget(builder, name));

}

