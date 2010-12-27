#include "ltk_combo_box.h"
#include "ltk_common.h"
#include <string.h>

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
}

void ltk_combo_box_connect_to_option(GtkComboBox *combo_box, LOptionList *options, const char *id) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	g_assert(options != NULL);
	g_assert(id != NULL && strlen(id) > 0);
	ltk_combo_box_set_active_value_from_option(combo_box, options, id);
	g_signal_connect(combo_box, "changed", G_CALLBACK(ltk_combo_box_changed), ltk_payload_new(options, id));
}

static void ltk_combo_box_changed_with_adjustment(GtkComboBox *combo_box, gpointer data) {
	GtkAdjustment *adjustment = GTK_ADJUSTMENT(data);
	LValue *value = ltk_combo_box_get_active_value(combo_box);
	if (value != NULL) {
		if (l_value_get_type(value) != L_TYPE_INT) {
			g_warning("combo box value type is not L_TYPE_INT");
		} else {
			gtk_adjustment_set_value(adjustment, l_value_get_int(value));
		}
	}
}

void ltk_combo_box_connect_to_adjustment(GtkComboBox *combo_box, GtkAdjustment *adjustment) {
	g_assert(combo_box != NULL);
	g_assert(ltk_object_is_marked(GTK_OBJECT(combo_box)));
	g_assert(adjustment != NULL);
	g_signal_connect(combo_box, "changed", G_CALLBACK(ltk_combo_box_changed_with_adjustment), adjustment);
}
