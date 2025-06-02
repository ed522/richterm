//SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <stdint.h>

typedef uint8_t colour_t;
typedef uint16_t attribute_t;

#define FG_BLACK			0x0
#define FG_RED				0x1
#define FG_GREEN			0x2
#define FG_YELLOW			0x3
#define FG_BLUE				0x4
#define FG_MAGENTA			0x5
#define FG_CYAN				0x6
#define FG_WHITE			0x7
#define BRIGHT_FG_BLACK		0x8
#define BRIGHT_FG_RED		0x9
#define BRIGHT_FG_GREEN		0xA
#define BRIGHT_FG_YELLOW 	0xB
#define BRIGHT_FG_BLUE 		0xC
#define BRIGHT_FG_MAGENTA 	0xD
#define BRIGHT_FG_CYAN 		0xE
#define BRIGHT_FG_WHITE 	0xF
#define BG_BLACK			0x00
#define BG_RED				0x10
#define BG_GREEN			0x20
#define BG_YELLOW			0x30
#define BG_BLUE				0x40
#define BG_MAGENTA			0x50
#define BG_CYAN				0x60
#define BG_WHITE			0x70
#define BRIGHT_BG_BLACK		0x80
#define BRIGHT_BG_RED		0x90
#define BRIGHT_BG_GREEN		0xA0
#define BRIGHT_BG_YELLOW 	0xB0
#define BRIGHT_BG_BLUE 		0xC0
#define BRIGHT_BG_MAGENTA 	0xD0
#define BRIGHT_BG_CYAN 		0xE0
#define BRIGHT_BG_WHITE 	0xF0

#define ATTRIB_BOLD			0x1
#define ATTRIB_FAINT		0x2
#define ATTRIB_ITALIC		0x4
#define ATTRIB_UNDERLINE	0x8
#define ATTRIB_BLINKSLOW	0x10
#define ATTRIB_BLINKFAST	0x20
#define ATTRIB_INVERT		0x40
#define ATTRIB_HIDE			0x80
#define ATTRIB_STRIKE		0x100
#define ATTRIB_FRAKTUR		0x200
#define ATTRIB_2UNDERLINE	0x400
#define ATTRIB_PROPORTIONAL	0x800
#define ATTRIB_FRAMED		0x1000
#define ATTRIB_CIRCLED		0x2000
#define ATTRIB_OVERLINE		0x4000

uint64_t get_term_size(void);
uint64_t get_cursor_pos(void);
int enter_raw(void);
int unraw(void);
int reset_terminal(void);

void clear(void);

void move(int x, int y);
void move_horizontal(int delta);
void move_vertical(int delta);
void home(void);

void colour_text(colour_t colour);
void colour_text_hi_fg(uint8_t colour);
void colour_text_hi_bg(uint8_t colour);
void colour_text_true_fg(uint32_t colour);
void colour_text_true_bg(uint32_t colour);
void modify_text(attribute_t attributes);
