#include "socket.h"

void Socket_SetBlocks(int fd, bool blocks)  {
	int flags = fcntl(fd, F_GETFL, 0);

	flags = blocks? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);

	fcntl(fd, F_SETFL, flags);
}
