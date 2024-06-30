#include <string.h>
#include "string.h"
#include "url.h"

Url ParseURL(const char* url) {
	Url ret;

	ret.valid  = true;
	ret.domain = String_New("");
	ret.port   = 140;
	ret.path   = String_New("");

	size_t i;
	for (i = 0; i < strlen(url); ++ i) {
		bool end = false;
		
		switch (url[i]) {
			case '/':
			case ':': {
				end = true;
				break;
			}
			default: {
				ret.domain = String_AddChar(ret.domain, url[i]);
			}
		}

		if (end) break;
	}

	// parse port
	if (url[i] == ':') {
		++ i;
		char* port = String_New("");

		for (; i < strlen(url); ++ i) {
			bool end = false;
		
			switch (url[i]) {
				case '/': {
					end = true;
					break;
				}
				default: {
					port = String_AddChar(port, url[i]);
				}
			}

			if (end) break;
		}

		ret.port = atoi(port);

		if (ret.port == 0) {
			ret.valid = false;
			return ret;
		}
	}

	// parse path
	for (; i < strlen(url); ++ i) {
		ret.path = String_AddChar(ret.path, url[i]);
	}

	return ret;
}

void FreeURL(Url* url) {
	free((char*) url->domain);
	free((char*) url->path);
}
