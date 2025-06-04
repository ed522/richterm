#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define HOOKBUF_SIZE_INITIAL 64;
#define HOOKBUF_SIZE_INCREMENT 32;

void setup(InputState *state) { //private

	// hooks must be NULL and size must be -1
	if (state->hooks != NULL || state->hookbuf_size != -1) return;
	hookbuf_size = HOOKBUF_SIZE_INITIAL;

	hooks = malloc(sizeof(Hook *) * hookbuf_size);
	
}
void teardown(void) {
	if (hooks == NULL || hookbuf_size == -1) return;
	for (int i = 0; i < hookbuf_size; i++) {
		if (hooks[i] != NULL) {
			free(hooks[i]);
			hooks[i] = NULL;
		}
	}
	free(hooks);
	hooks = NULL;
	hookbuf_size = -1;
}

void input_thread(void) {
	// MUST be in a separate thread
	// cancel with pthread_cancel
	while (1) {
		
	}
}

#undef HOOKBUF_SIZE_INITIAL
#undef HOOKBUF_SIZE_INCREMENT
