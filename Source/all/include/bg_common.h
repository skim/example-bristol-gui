#ifndef BG_COMMON_BASIC_H_
#define BG_COMMON_BASIC_H_

typedef struct {
	char *name;
	char *value;
} BgComboEntry;


char *bg_make_path(const char *filename);
BgComboEntry* bg_combo_entry_new(const char *name, const char *value);


#endif /* BG_COMMON_BASIC_H_ */
