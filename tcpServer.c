#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include<pthread.h>


int dealRecv(char* receive,int fd);
void *recv_fun(void *p)
{
	int fd; 
	int *q = p;
	fd  = *q;		//fd = *((int *)p);
	char buf[100] = { 0 };
	while(1)
	{
		if(recv(fd, buf, sizeof(buf), 0) <= 0)
			return 0;
        dealRecv(buf,fd);
		printf("recv is %s\n", buf);
		send(fd, buf, sizeof(buf), 0);    //这个注释掉，通信就无法进行，而且客户端会退出。这个需要注意
                                           //先解决一下这个问题，如果实在解决不了就取消使用函数 
	}
}
int main(int argc, char *argv[])
{	
	pthread_t id;
	char buf[100] = { 0 };
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(55555);   //不要超过65535
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //inet_addr("127.0.0.1");
	bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	listen(fd, 5);
	while(1)
	{
		int newfd =  accept(fd, NULL, NULL);		//阻塞等待客户端连接
		pthread_create(&id, NULL, recv_fun, &newfd);	//一旦有客户端连接，就创建新线程
	}
    return 0;
}


int dealRecv(char* receive,int fd)
{
    char *p,*q;
    if(strcmp(receive,"quit")==0)
    {
        printf("一个客户端成功退出\n"); 
        pthread_cancel(fd);             
    }
    else
    {
        p=strtok(receive," ");
        q=strtok(NULL," ");       //将字符串分割
        if(strcmp(p,"get")==0)
        {
            printf("客户端请求下载文件:%s\n",q);
        }
        else if(strcmp(p,"put")==0)
        {
            printf("客户端将要上传文件:%s\n",q);
        }
    }
}