#pragma once
#include <stdint.h>

typedef uint8_t char_mod;

typedef struct {
	char key;
	char_mod modifiers;
	void (* callback) (char, char_mod);
	uint8_t options;
} Hook;

typedef struct {
	Hook **hooks;
	int hookbuf_size;
} InputState;

#define MODIFIER_NONE	0
#define MODIFIER_CTRL	1
#define MODIFIER_SHIFT	2
#define MODIFIER_ALT	4
#define MODIFIER_META	8

#define SPECIAL_F1		0
#define SPECIAL_F2		1
#define SPECIAL_F3		2
#define SPECIAL_F4		3
#define SPECIAL_F5		4
#define SPECIAL_F6		5
#define SPECIAL_F7		6
#define SPECIAL_F8		7
#define SPECIAL_F9		8
#define SPECIAL_F10		9
#define SPECIAL_F11		10
#define SPECIAL_F12		11
#define SPECIAL_UP		12
#define SPECIAL_DOWN	13
#define SPECIAL_LEFT	14
#define SPECIAL_RIGHT	15
#define SPECIAL_PGUP	16
#define SPECIAL_PGDOWN	17
#define SPECIAL_INS	 	18
#define SPECIAL_DELETE	19
#define SPECIAL_HOME	20
#define SPECIAL_END	 	21

void hook_plain(char key, char_mod modifiers, void callback(char, char_mod), InputState *state);
void hook_special(char key, char_mod modifiers, void callback(char, char_mod), InputState *state);
void hook_all(void callback(char, char_mod), InputState *state);
void input_start(InputState *state);
void input_end(InputState *state);
