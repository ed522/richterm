//SPDX-License-Identifier: GPL-3.0-only
#include "term.h"
#include "codes.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

// lookup
char foreground[16][2] = {
	SGR_FG_BLACK,
	SGR_FG_RED,
	SGR_FG_GREEN,
	SGR_FG_YELLOW,
	SGR_FG_BLUE,
	SGR_FG_MAGENTA,
	SGR_FG_CYAN,
	SGR_FG_WHITE,
	SGR_FG_BRIGHT_BLACK,
	SGR_FG_BRIGHT_RED,
	SGR_FG_BRIGHT_GREEN,
	SGR_FG_BRIGHT_YELLOW,
	SGR_FG_BRIGHT_BLUE,
	SGR_FG_BRIGHT_MAGENTA,
	SGR_FG_BRIGHT_CYAN,
	SGR_FG_BRIGHT_WHITE
};
char background[16][2] = {
	SGR_BG_BLACK,
	SGR_BG_RED,
	SGR_BG_GREEN,
	SGR_BG_YELLOW,
	SGR_BG_BLUE,
	SGR_BG_MAGENTA,
	SGR_BG_CYAN,
	SGR_BG_WHITE,
	SGR_BG_BRIGHT_BLACK,
	SGR_BG_BRIGHT_RED,
	SGR_BG_BRIGHT_GREEN,
	SGR_BG_BRIGHT_YELLOW,
	SGR_BG_BRIGHT_BLUE,
	SGR_BG_BRIGHT_MAGENTA,
	SGR_BG_BRIGHT_CYAN,
	SGR_BG_BRIGHT_WHITE
};
char attrib_table[15][2] = {
	SGR_BOLD, SGR_FAINT, SGR_ITALIC, SGR_UNDERLINE,
	SGR_BLINKSLOW, SGR_BLINKFAST, SGR_INVERT, SGR_HIDE,
	SGR_STRIKETHROUGH, SGR_FRAKTUR, SGR_2UNDERLINE_NOBOLD,
	SGR_PROPORTIONAL, SGR_FRAMED, SGR_CIRCLED, SGR_OVERLINED
};

struct termios *term_before = NULL;

uint64_t get_term_size(void) {
	uint32_t w, h;
	struct winsize *size = malloc(sizeof(struct winsize));
	ioctl(0, TIOCGWINSZ, size);
	w = size->ws_col;
	h = size->ws_row;
	return w | ((uint64_t) h << 32);
}
uint64_t get_cursor_pos(void) {
	uint32_t x = 0, y = 0;
	fputs(FE_CSI CSI_GET_CURPOS, stdout);
	scanf("\x1B[%u;%uR", &y, &x);
	return x | ((uint64_t) y << 32);
}
/**
 * Enter raw terminal mode
 * Returns:
 *  - on success: 0
 *  - on syscall error: -1, errno set
 *  - if the terminal is already raw: -2
 */
int enter_raw(void) {

	struct termios *term = malloc(sizeof(struct termios));
	int result = tcgetattr(0, term);
	if (result != 0) return result;
	
	if (term_before == NULL) {
		term_before = malloc(sizeof(struct termios));
		if (term_before == NULL) {
			return -1;
		}
		memcpy(term_before, term, sizeof(struct termios));
	} else {
		return -2;
	}
	
	cfmakeraw(term);
	return tcsetattr(0, TCSANOW, term);
	
}
/**
 * Exit raw terminal mode, if it was already entered
 * Returns:
 *  - on success: 0
 *  - on syscall error: -1, errno set
 *  - if the terminal was never raw, or has already been unrawed/reset: -2
 */
int unraw(void) {

	if (term_before == NULL) {
		return -2;
	}
	int result = tcsetattr(0, TCSANOW, term_before);
	free(term_before);
	term_before = NULL;
	if (errno != 0) return -1;
	return result;
	
}
/**
 * Reset all characteristics of the terminal, and 
 * Returns:
 *  - on success: 0
 *  - on syscall error: -1, errno set
 */
int reset_terminal(void) {
	if (term_before != NULL) {
		free(term_before);
		if (errno != 0) return -1;
		term_before = NULL;
	}
	return system("reset");
}

void clear(void) {
	fputs(FE_CSI CSI_ERASE_ALL CSI_ERASE, stdout);
}

void move(int x, int y) {
	printf(FE_CSI "%u;%u" CSI_CURSOR_ABSOLUTE, y + 1, x + 1);
}
void move_horizontal(int delta) {
	if (delta >= 0) {
		printf(FE_CSI "%u" CSI_CURSOR_FORWARD, delta);
	} else {
		printf(FE_CSI "%u" CSI_CURSOR_BACK, -delta);
	}
}
void move_vertical(int delta) {
	if (delta >= 0) {
		printf(FE_CSI "%u" CSI_CURSOR_DOWN, delta);
	} else {
		printf(FE_CSI "%u" CSI_CURSOR_UP, -delta);
	}
}
void home(void) {
	fputs("\r", stdout);
}

void colour_text(colour_t colour) {
	uint8_t fore = colour & 0xF;
	uint8_t back = (colour & 0xF0) >> 4;
	printf(FE_CSI "%s;%s" SGR_TERM, foreground[fore], background[back]);
}
void colour_text_hi_fg(uint8_t colour) {
	printf(FE_CSI SGR_FG_HICOLOUR ";" SGR_COLOUR_256 ";%u" SGR_TERM, colour);
}
void colour_text_hi_bg(uint8_t colour) {
	printf(FE_CSI SGR_BG_HICOLOUR ";" SGR_COLOUR_256 ";%u" SGR_TERM, colour);
}
void colour_text_true_fg(uint32_t colour) {
	uint8_t r, g, b;
	b = colour & 0xFF;
	colour >>= 8;
	g = colour & 0xFF;
	colour >>= 8;
	r = colour & 0xFF;
	
	printf(FE_CSI SGR_FG_HICOLOUR ";" SGR_COLOUR_TRUE ";%u;%u;%u" SGR_TERM,
		r, g, b);
}
void colour_text_true_bg(uint32_t colour) {
	uint8_t r, g, b;
	b = colour & 0xFF;
	colour >>= 8;
	g = colour & 0xFF;
	colour >>= 8;
	r = colour & 0xFF;
	
	printf(FE_CSI SGR_BG_HICOLOUR ";" SGR_COLOUR_TRUE ";%u;%u;%u" SGR_TERM,
		r, g, b);
}
void modify_text(attribute_t attributes) {
	fputs(FE_CSI SGR_RESET, stdout); //unterminated
	uint32_t i = 0;
	while (attributes != 0) {
		if (i >= sizeof(attrib_table) / 2 /* element size */) break;
		int present = attributes & 1;
		if (present) fputs(attrib_table[i], stdout);
		i++;
	}
}
