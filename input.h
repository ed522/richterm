#pragma once

#define MODIFIER_NONE	0
#define MODIFIER_CTRL	1
#define MODIFIER_SHIFT	2
#define MODIFIER_ALT	4
#define MODIFIER_META	8

#define SPECIAL_F10		0
#define SPECIAL_F2		0
#define SPECIAL_F3		0
#define SPECIAL_F4		0
#define SPECIAL_F5		0
#define SPECIAL_F6		0
#define SPECIAL_F7		0
#define SPECIAL_F8		0
#define SPECIAL_F1		0
#define SPECIAL_F9		0
#define SPECIAL_F10		0
#define SPECIAL_F11		0
#define SPECIAL_F12		0
#define SPECIAL_UP		0
#define SPECIAL_DOWN	0
#define SPECIAL_LEFT	0
#define SPECIAL_RIGHT	0
#define SPECIAL_PGUP	0
#define SPECIAL_PGDOWN	0
#define SPECIAL_INS	 	0
#define SPECIAL_DELETE	0
#define SPECIAL_HOME	0
#define SPECIAL_END	 	0

void hook_plain(char key, char modifiers, void *callback(void));
void hook_special(char key, char modifiers, void *callback(void));
void start(void);
void end();
