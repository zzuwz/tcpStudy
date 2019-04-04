#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>


int dealRecv(char* receive);

int fd;
char receive[100] = { 0 };
void *recv_fun(void *p)     //接收的线程
{
	while(1)
	{
		int ret = recv(fd, receive, sizeof(receive), 0);	//阻塞
		if(ret > 0)
			printf("recv is %s\n", receive);
	}
}


int main(int argc, char *argv[])
{
    pthread_t id;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in youaddr;
	youaddr.sin_family = AF_INET;
	youaddr.sin_port = htons(atoi(argv[2]));   //不要超过65535
	youaddr.sin_addr.s_addr = inet_addr(argv[1]);	//ip地址
	connect(fd, (struct sockaddr *)&youaddr, sizeof(youaddr));
	pthread_create(&id, NULL, recv_fun, NULL);
    while(1)
    {
        printf(">>>");
        gets(receive);
        send(fd, receive, strlen(receive) + 1, 0);
        int i=dealRecv(receive);
        //if(i==1)
        //{
        //    return 0;
        //}
    }
    return 0;
}

int dealRecv(char* receive)
{
    char *p,*q;
    //char receive[100] = { 0 };
    //receive=rec;
    if(strcmp(receive,"help")==0)
    {
        printf("enter help\n");
    }
    else if(strcmp(receive,"list")==0)
    {
        printf("打印列表\n");
    }
    else if(strcmp(receive,"quit")==0)
    {
        printf("成功退出\n");
        return 1;
    }
    else
    {
        p=strtok(receive," ");
        q=strtok(NULL," ");       //将字符串分割
        if(strcmp(p,"get")==0)
        {
            printf("下载文件:%s\n",q);
        }
        else if(strcmp(p,"put")==0)
        {
            printf("上传文件:%s\n",q);
        }
        else
        {
        //printf("%s\n%s\n",p,q);
        //printf("%s\n",receive);
        printf("输入命令错误\n");                
        }
    }
}