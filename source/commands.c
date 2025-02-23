#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "app.h"
#include "url.h"
#include "safe.h"
#include "socket.h"
#include "commands.h"

void Command_Help(char** args, size_t length) {
	App* app = App_Instance();

	for (size_t i = 0; i < app->cmds.numCmds; ++ i) {
		puts(app->cmds.cmds[i].name);
	}
}

#define RECV(FD, BUF, LEN, FLAGS) \
	if (recv(FD, BUF, LEN, FLAGS) < 0) { \
		perror("recv"); \
		return; \
	}

#define SEND(FD, BUF, LEN, FLAGS) \
	if (send(FD, BUF, LEN, FLAGS) < 0) { \
		perror("send"); \
		return; \
	}

void Command_Goto(char** args, size_t length) {
	App* app = App_Instance();

	Url url = ParseURL(args[1]);

	if (!url.valid) {
		fprintf(stderr, "Invalid URL\n");
		return;
	}

	printf("Domain: %s\n", url.domain);
	printf("Port: %d\n", url.port);
	printf("Path: %s\n", url.path);

	if (strcmp(url.domain, "")) {
		if (app->sock <= 0) {
			puts("Closing existing connection..");
			close(app->sock);
		}

		app->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (app->sock < 0) {
			perror("socket");
		}

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port   = htons(url.port);

		if (inet_pton(AF_INET, url.domain, &addr.sin_addr) < 0) {
			fprintf(stderr, "Invalid address: '%s'\n", args[1]);
			return;
		}

		if (connect(app->sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
			perror("connect");
			return;
		}

		puts("Connected");
	}

	// send get request
	uint8_t packetID = 'G';
	char    newLine  = '\n';
	SEND(app->sock, &packetID, 1, 0);
	SEND(app->sock, url.domain, strlen(url.domain), 0);
	SEND(app->sock, &newLine, 1, 0);
	SEND(app->sock, url.path, strlen(url.path), 0);
	SEND(app->sock, &newLine, 1, 0);

	bool responseCompleted = false;
	while (!responseCompleted) {
		uint8_t packetID;

		RECV(app->sock, &packetID, 1, MSG_WAITALL);

		switch (packetID) {
			case 'G': {
				uint8_t  errorCode;
				uint64_t length;
				uint8_t* contents;

				RECV(app->sock, &errorCode, 1, MSG_WAITALL);
				RECV(app->sock, &length, sizeof(length), MSG_WAITALL);

				length   = ntohll(length);
				contents = SafeMalloc(length);

				RECV(app->sock, contents, length, MSG_WAITALL);

				printf("Recieved %ld bytes from server\n", length);

				for (size_t i = 0; i < length; ++ i) {
					putchar(contents[i]);
				}

				puts("\nRequest completed");
				responseCompleted = true;
				break;
			}
			default: {
				fprintf(stderr, "Invalid packet 0x%.2X\n", packetID);
				return;
			}
		}
	}

	FreeURL(&url);
}
