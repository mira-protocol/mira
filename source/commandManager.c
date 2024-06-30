#include <assert.h>
#include <string.h>
#include "safe.h"
#include "commands.h"
#include "commandManager.h"

CommandManager CommandManager_New(void) {
	CommandManager ret = {
		.cmds = NULL,
		.numCmds = 0
	};

	CommandManager_Add(&ret, (Command) {
		"help", 0, &Command_Help
	});
	CommandManager_Add(&ret, (Command) {
		"goto", 1, &Command_Goto
	});
	return ret;
}

void CommandManager_Add(CommandManager* manager, Command cmd) {
	manager->cmds = SafeRealloc(manager->cmds, (manager->numCmds + 1) * sizeof(Command));

	manager->cmds[manager->numCmds] = cmd;
	++ manager->numCmds;
}

bool CommandManager_Exists(CommandManager* manager, const char* cmd) {
	for (size_t i = 0; i < manager->numCmds; ++ i) {
		if (!strcmp(manager->cmds[i].name, cmd)) return true;
	}

	return false;
}

Command* CommandManager_Get(CommandManager* manager, const char* cmd) {
	for (size_t i = 0; i < manager->numCmds; ++ i) {
		if (!strcmp(manager->cmds[i].name, cmd)) return &manager->cmds[i];
	}

	assert(0);
}
