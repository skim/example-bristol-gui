#ifndef LLIB_COMMON_H_
#define LLIB_COMMON_H_

#define L_INT_UNDEFINED G_MAXINT

typedef enum {
	L_TYPE_STRING,
	L_TYPE_INT
} LType;

char* l_data_path_new(const char *filename);

#endif /* LLIB_COMMON_H_ */
