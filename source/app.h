#ifndef MIRA_APP_H
#define MIRA_APP_H

#include "commandManager.h"

typedef struct {
	bool           running;
	CommandManager cmds;
	int            sock;
} App;

App* App_Instance(void);
void App_Run(void);

#endif
