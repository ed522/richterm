#include "pane.h"
#include <stdio.h>

void render_pane(Pane *pane) {

	// wait until top
	for (uint32_t i = 0; i < pane->x; i++) {
		puts("\n");
	}
	
	// header
	for (uint32_t i = 0; i < pane->x; i++) {
		puts(" ");
	}
	char str[2] = {pane->top_edge_char, '\0'};
	for (uint32_t i = 0; i < pane->w + 2; i++) {
		puts(str);
	}
	puts("\n");

	for (uint32_t i = 0; i < pane->h; i++) {
		for (uint32_t i = 0; i < pane->x; i++) {
			puts(" ");
		}
		str[0] = pane->left_edge_char;
		puts(str);
		for (uint32_t i = 0; i < pane->w; i++) {
			puts("*");
		}
		str[0] = pane->right_edge_char;
		puts(str);
	}
	// footer
	for (uint32_t i = 0; i < pane->x; i++) {
		puts(" ");
	}
	str[0] = pane->bottom_edge_char;
	for (uint32_t i = 0; i < pane->w + 2; i++) {
		puts(str);
	}
	puts("\n");
	
}
