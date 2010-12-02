#ifndef GUI_H_
#define GUI_H_

void bg_prepare_combo_soundengine(const char *name);
void bg_prepare_entry_identifier(const char *name, const char *identifier);
void bg_prepare_adjust_samplerate(const char *name, unsigned int samplerate);
void bg_prepare_adjust_midichannel(const char *name, unsigned int midichannel);
void bg_show_help(const char *text_name);
void bg_start_synth(const char *synth_name);

#endif /* GUI_H_ */
