#include <stdio.h>

typedef struct buffer
{
	int rpid,spid;
}buffer;

void buffer_init(buffer *buff)
{
	buff->rpid= -10;
	buff->spid= -10;
}
