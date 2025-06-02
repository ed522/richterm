//SPDX-License-Identifier: GPL-3.0-only
#include "pane.h"
#include "codes.h"
#include "term.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_pane(Pane *pane) {

	char *linebuf = malloc((1 + pane->w) * sizeof(char));
	// clear
	clear();
	// go to top left corner
	move(pane->x, pane->y);

	for (uint32_t i = 0; i < pane->w + 2; i++) {
		fputc(pane->top_edge_char, stdout);
	}
	fputs("\n", stdout);

	for (uint32_t i = 0; i < pane->h; i++) {
		home();
		move_horizontal(pane->x);
		fputc(pane->left_edge_char, stdout);
		if ((long int) i < pane->linecount){
			char *line = pane->contents[i];
			
			int logical_height = (pane->logical_heights == NULL) ? 1 : pane->logical_heights[i];
			int len = 
				(pane->logical_widths == NULL) ? 
				(int) strlen(line) : pane->logical_widths[i];
			
			if (len < (int) pane->w) memcpy(linebuf, line, len);
			else {
				memcpy(linebuf, line, pane->w * sizeof(char));
				linebuf[pane->w] = '\0';
			}
			fputs(linebuf, stdout);
			i += logical_height - 1;
		}
		move(pane->x + pane->w + 1, pane->y + 1 + i);
		fputc(pane->right_edge_char, stdout);
		move_vertical(1);
	}
	home();
	move_horizontal(pane->x);
	// footer
	for (uint32_t i = 0; i < pane->w + 2; i++) {
		fputc(pane->bottom_edge_char, stdout);
	}
	fputs("\n", stdout);
	free(linebuf);
	
}

void render_scene(Scene *scene) {
	for (int i = 0; i < scene->count; i++) {
		render_pane(scene->panes[i]);
	}
}
