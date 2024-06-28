#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "app.h"
#include "commands.h"

void Command_Help(char** args, size_t length) {
	App* app = App_Instance();

	for (size_t i = 0; i < app->cmds.numCmds; ++ i) {
		puts(app->cmds.cmds[i].name);
	}
}

void Command_Goto(char** args, size_t length) {
	App* app = App_Instance();

	if (app->sock != -1) {
		puts("Closing existing connection..");
		close(app->sock);
	}

	app->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (app->sock < 0) {
		perror("socket");
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(atoi(args[2]));

	if (inet_pton(AF_INET, args[1], &addr.sin_addr) < 0) {
		fprintf(stderr, "Invalid address: '%s'\n", args[1]);
		return;
	}

	if (connect(app->sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("connect");
		return;
	}

	puts("Connected");
}
