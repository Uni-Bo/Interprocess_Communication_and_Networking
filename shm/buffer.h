#include <string.h>
typedef struct buffer
{
	int cpid,spid;
	char buff[300];
}buffer;

void buff_init(buffer* buffer)
{
	buffer->cpid=-10;
	buffer->spid=-10;
	strcpy(buffer->buff,"/0");
}
