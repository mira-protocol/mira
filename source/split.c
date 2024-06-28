#include <string.h>
#include "safe.h"
#include "split.h"
#include "string.h"

char** Split(const char* str, size_t* length) {
	char** ret;
	*length = 0;

	ret    = SafeMalloc(sizeof(char*));
	ret[0] = NULL;

	char* thisString = String_New("");

	for (size_t i = 0; i <= strlen(str); ++ i) {
		switch (str[i]) {
			case ' ':
			case '\t':
			case '\0': {
				ret[*length] = thisString;
				++ *length;

				ret = SafeRealloc(ret, sizeof(char*) * (*length + 1));
				ret[*length] = NULL;

				thisString = String_New("");
				break;
			}
			default: {
				String_AddChar(thisString, str[i]);
				break;
			}
		}
	}

	return ret;
}
