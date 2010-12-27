#include "ltk_common.h"
#include "string.h"

typedef struct {
	LOptionList *options;
	char *id;
} LtkPayload;

static LtkPayload* ltk_payload_new(LOptionList *options, const char *id) {
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	LtkPayload *payload = g_new(LtkPayload, 1);
	payload->options = options;
	payload->id = g_strdup(id);
	return payload;
}

static void ltk_object_mark(GtkObject *object) {
	g_assert(object != NULL);
	g_object_set_data(G_OBJECT(object), LTK_OBJECT_MARK_KEY, GINT_TO_POINTER(1));
}

static gboolean ltk_object_is_marked(GtkObject *object) {
	g_assert(object != NULL);
	return g_object_get_data(G_OBJECT(object), LTK_OBJECT_MARK_KEY) != NULL;
}

void ltk_button_set_stock_image(GtkButton *button, const char *stock_name, GtkIconSize size) {
	g_assert(button != NULL);
	g_assert(stock_name != NULL && strlen(stock_name) > 0);
	gtk_button_set_image(button, gtk_image_new_from_stock(stock_name, size));
}

void ltk_combo_box_fill(GtkComboBox *combo_box, LValueList *values) {
	g_assert(combo_box != NULL);
	g_assert(values != NULL);
	ltk_object_mark(GTK_OBJECT(combo_box));
	GtkListStore *store = NULL;
	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_POINTER);
	GtkTreeIter iter;
	int i;
	for (i = 0; i < l_value_list_length(values); i++) {
		gtk_list_store_append(store, &iter);
		LValue *value = l_value_list_nth_value(values, i);
		gtk_list_store_set(store, &iter, 0, l_value_list_nth_display_name(values, i), 1, value, -1);
	}
	gtk_combo_box_set_model(combo_box, GTK_TREE_MODEL(store));
	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo_box), renderer, FALSE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo_box), renderer, "text", 0, NULL);
	gtk_combo_box_set_active(combo_box, 0);
}

static LValue* ltk_combo_box_get_nth_value(GtkComboBox *combo_box, int index) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_combo_box_get_model(combo_box);
	if (!gtk_tree_model_iter_nth_child(model, &iter, NULL, index)) {
		g_warning("combo box has no value at index: %d", index);
	} else {
		LValue *value;
		gtk_tree_model_get(model, &iter, 1, &value, -1);
		return value;
	}
	return NULL;
}

static int ltk_combo_box_get_value_length(GtkComboBox *combo_box) {
	g_assert(combo_box != NULL);
	GtkTreeModel *model = gtk_combo_box_get_model(combo_box);
	return gtk_tree_model_iter_n_children(model, NULL);
}

void ltk_combo_box_set_active_value(GtkComboBox *combo_box, LValue *value_) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	int i;
	for (i = 0; i < ltk_combo_box_get_value_length(combo_box); i++) {
		LValue *value = ltk_combo_box_get_nth_value(combo_box, i);
		if (l_value_equals(value, value_)) {
			gtk_combo_box_set_active(combo_box, i);
			break;
		}
	}
}

LValue* ltk_combo_box_get_active_value(GtkComboBox *combo_box) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	return ltk_combo_box_get_nth_value(combo_box, gtk_combo_box_get_active(combo_box));
}

void ltk_combo_box_set_active_value_from_option(GtkComboBox *combo_box, LOptionList *options, const char *id) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	if (l_option_list_get_value(options, id) != NULL) {
		ltk_combo_box_set_active_value(combo_box, l_option_list_get_value(options, id));
	}
}

static void ltk_combo_box_changed(GtkComboBox *combo_box, gpointer data) {
	LtkPayload *payload = (LtkPayload*) data;
	l_option_list_set_value(payload->options, payload->id, ltk_combo_box_get_active_value(combo_box));
	g_debug("combo_box_changed");
}

void ltk_combo_box_connect_option(GtkComboBox *combo_box, LOptionList *options, const char *id) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	ltk_combo_box_set_active_value_from_option(combo_box, options, id);
	g_signal_connect(combo_box, "changed", G_CALLBACK(ltk_combo_box_changed), ltk_payload_new(options, id));
}

void ltk_toggle_button_set_active_from_option(GtkToggleButton *toggle, LOptionList *options, const char *id) {
	g_assert(toggle != NULL);
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	if (l_option_list_get_value(options, id) != NULL) {
		gtk_toggle_button_set_active(toggle, l_value_is_enabled(l_option_list_get_value(options, id)));
	}
}

static void ltk_toggle_button_clicked(GtkToggleButton *toggle, gpointer data) {
	LtkPayload *payload = (LtkPayload*) data;
	if (l_option_list_get_value(payload->options, payload->id) != NULL) {
		l_value_set_enabled(l_option_list_get_value(payload->options, payload->id), gtk_toggle_button_get_active(toggle));
	} else {
		g_warning("option: %s enabled but not set", payload->id);
	}
}

void ltk_toggle_button_connect_option(GtkToggleButton *toggle, LOptionList *options, const char *id) {
	g_assert(toggle != NULL);
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	ltk_toggle_button_set_active_from_option(toggle, options, id);
	g_signal_connect(toggle, "clicked", G_CALLBACK(ltk_toggle_button_clicked), ltk_payload_new(options, id));
}
