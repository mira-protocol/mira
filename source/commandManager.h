#ifndef MIRA_COMMAND_MANAGER_H
#define MIRA_COMMAND_MANAGER_H

#include "common.h"

typedef struct {
	const char* name;
	size_t      requiredArgs;
	void        (*func)(char** args, size_t length);
} Command;

typedef struct {
	Command* cmds;
	size_t   numCmds;
} CommandManager;

CommandManager CommandManager_New(void);
void           CommandManager_Add(CommandManager* manager, Command cmd);
bool           CommandManager_Exists(CommandManager* manager, const char* cmd);
Command*       CommandManager_Get(CommandManager* manager, const char* cmd);

#endif
