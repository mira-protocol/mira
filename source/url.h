#ifndef MIRA_URL_H
#define MIRA_URL_H

#include "common.h"

typedef struct {
	bool        valid;
	const char* domain;
	uint16_t    port;
	const char* path;
} Url;

Url  ParseURL(const char* url);
void FreeURL(Url* url);

#endif
