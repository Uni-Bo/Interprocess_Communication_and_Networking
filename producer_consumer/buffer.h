
typedef struct buffer
{
	int front,rear;
	int buff[5];
}buffer;

void buff_init(buffer* buffer)
{
	buffer->front=buffer->rear=-1;
}

void push(buffer* buff, int in)
{
	buff->rear=buff->rear+1;
	buff->buff[buff->rear]=in;
	
	if(buff->front==-1)
	{
		buff->front=0;
	}
}

int pop(buffer* buff)
{
	int x= buff->buff[buff->front];
	buff->front=buff->front+1;
	
	if(buff->front>buff->rear)
	{
		buff->rear=-1;
		buff->front=-1;
	}
	
	return x;
}


	
	
