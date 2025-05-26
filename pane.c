//SPDX-License-Identifier: GPL-3.0-only
#include "pane.h"
#include "codes.h"
#include <stdio.h>
#include <stdlib.h>

void render_pane(Pane *pane) {

	// reset position/clear
	fputs(FE_CSI CSI_ERASE_ALL CSI_ERASE FE_CSI "0;0" CSI_CURSOR_ABSOLUTE, stdout);

	// go to top left corner
	printf(FE_CSI "%u;%u" CSI_CURSOR_ABSOLUTE, pane->y + 1, pane->x + 1);

	char str[2] = {pane->top_edge_char, '\0'};
	for (uint32_t i = 0; i < pane->w + 2; i++) {
		fputs(str, stdout);
	}
	fputs("\n", stdout);

	for (uint32_t i = 0; i < pane->h; i++) {
		for (uint32_t i = 0; i < pane->x; i++) {
			fputs(" ", stdout);
		}
		str[0] = pane->left_edge_char;
		fputs(str, stdout);
		for (uint32_t i = 0; i < pane->w; i++) {
			fputs("*", stdout);
		}
		str[0] = pane->right_edge_char;
		fputs(str, stdout);
		fputs("\n", stdout);
	}
	// footer
	for (uint32_t i = 0; i < pane->x; i++) {
		fputs(" ", stdout);
	}
	str[0] = pane->bottom_edge_char;
	for (uint32_t i = 0; i < pane->w + 2; i++) {
		fputs(str, stdout);
	}
	fputs("\n", stdout);
	
}
