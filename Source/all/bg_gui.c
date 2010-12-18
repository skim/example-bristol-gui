#include "bg_gui.h"
#include "bg_config.h"

static void bg_gui_switched(GtkButton *button, gpointer data) {
	BgGuiPayload *payload = (BgGuiPayload*) data;
	GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(payload->builder, bg_gui_name(payload->id, "box")));
	gtk_widget_set_visible(box, !gtk_widget_get_visible(box));
	char *stock_name = gtk_widget_get_visible(box) ? BG_STOCK_HIDE : BG_STOCK_SHOW;
	GtkWidget *image = gtk_image_new_from_stock(stock_name, GTK_ICON_SIZE_MENU);
	gtk_button_set_image(button, image);
}

static void bg_gui_toggled(GtkCheckButton *check, gpointer data) {
	GtkWidget *label = gtk_bin_get_child(GTK_BIN(check));
	BgGuiPayload *load = (BgGuiPayload*) data;
	gtk_widget_set_sensitive(label, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)));
	char *box_name = bg_gui_name(load->id, "box");
	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(load->builder, box_name)), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check)));
}

char *bg_gui_name(const char *id, const char *widget) {
	return g_strdup_printf("%s_%s", widget, id);
}

BgGuiPayload *bg_gui_payload_new(GtkBuilder *builder, const char *id) {
	BgGuiPayload *load = g_new(BgGuiPayload, 1);
	load->builder = builder;
	load->id = g_strdup(id);
	return load;
}

void bg_gui_checkbox_prepare(GtkBuilder *builder, const char *id, gboolean active) {
	GtkCheckButton *check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "check")));
	BgGuiPayload *payload = bg_gui_payload_new(builder, id);
	g_signal_connect(check, "toggled", G_CALLBACK(bg_gui_toggled), payload);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), active);
	bg_gui_toggled(check, payload);
}

void bg_gui_combobox_prepare(GtkBuilder *builder, const char *id) {

}

void bg_gui_adjust_set_value(GtkBuilder *builder, const char *id, double value) {
	GtkAdjustment *adjust = GTK_ADJUSTMENT(gtk_builder_get_object(builder, bg_gui_name(id, "adjust")));
	gtk_adjustment_set_value(adjust, value);
}

void bg_gui_switch_prepare(GtkBuilder *builder, const char *id) {
	GtkButton *button = GTK_BUTTON(gtk_builder_get_object(builder, bg_gui_name(id, "switch")));
	BgGuiPayload *payload = bg_gui_payload_new(builder, id);
	g_signal_connect(button, "clicked", G_CALLBACK(bg_gui_switched), payload);
}
