//SPDX-License-Identifier: GPL-3.0-only
#pragma once
#include <stdint.h>

typedef struct {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	
	char bottom_edge_char;
	char top_edge_char;
	char left_edge_char;
	char right_edge_char;

	int bufferSize;
	char **data;
} Pane;
typedef struct {
	int count;
	Pane **panes;
} Scene;

void render_pane(Pane *pane);
void render_scene(Scene *scene);

