#include <stdio.h>
#include <readline/readline.h>
#include "app.h"
#include "split.h"

static App app;

App* App_Instance(void) {
	return &app;
}

void App_Run(void) {
	app.cmds    = CommandManager_New();
	app.running = true;
	app.sock    = -1;

	puts("Welcome to Mira");

	while (app.running) {
		char* input = readline(">> ");
		size_t length;
		char** parts = Split(input, &length);

		if (!CommandManager_Exists(&app.cmds, parts[0])) {
			fprintf(stderr, "Command '%s' doesn't exist\n", parts[0]);
			goto next;
		}

		Command* cmd = CommandManager_Get(&app.cmds, parts[0]);
		cmd->func(parts, length);

		next:
		free(input);
	}
}
