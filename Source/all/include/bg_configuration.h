#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

typedef enum {
	BG_JACK,
	BG_ALSA,
	BG_PULSE,
	BG_OSS
} BG_SOUNDENGINE;

typedef struct {
	char *name;
	BG_SOUNDENGINE soundengine;
	char *identifier;
	unsigned int samplerate;
	unsigned int periodsize;
	unsigned int midichannel;
} bg_configuration;

bg_configuration* bg_configuration_new(const char *name);


#endif /* CONFIGURATION_H_ */
