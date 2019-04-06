#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int dealRecv(char* receive);
void dealServerMessage(char* receive);
void *recv_fun(void *p) ;
int fd;
int fileid1;
char receive[1024] = { 0 };
int order=0;
int allFlag=0;

int main(int argc, char *argv[])
{
    int i=0;
    char myreceive[1024]={0};
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
        //printf(">>>");
        gets(myreceive);
        send(fd, myreceive, strlen(myreceive) + 1, 0);
        i=dealRecv(myreceive);
        //printf("%d\n",i);
        if(i==1)
        {
            return 0;
        }
    }
    return 0;
}


int dealRecv(char* receive)
{
    char *p,*q;
    if(strcmp(receive,"help")==0)
    {
        printf("enter help\n");
    }
    else if(strcmp(receive,"list")==0)
    {
        printf("打印列表\n");
        order=0;
        allFlag=1;
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
            fileid1=open(q,O_RDWR | O_CREAT | O_TRUNC, 0666);
            allFlag=2;
        }
        else if(strcmp(p,"put")==0)
        {
            printf("上传文件:%s\n",q);
            int fileid2=open(q,O_RDONLY);
            int len=0;
            if(fileid2>0)
            {
                char fileBuf[1024] = { 0 };
                while((len = read(fileid2, fileBuf, sizeof(fileBuf))) > 0)
				{
                    send(fd,fileBuf,len,0);
                    memset(fileBuf,0,sizeof(fileBuf));
                }
                close(fileid2);
                send(fd,"receiveOk",sizeof("receiveOk"),0);
            }
            allFlag=3;
        }
        else
        {
        //printf("%s\n%s\n",p,q);
        //printf("%s\n",receive);
        printf("输入命令错误\n");                
        }
    }
    return 0;
}


void *recv_fun(void *p)     //接收的线程
{
    
	while(1)
	{
		int ret = recv(fd, receive, sizeof(receive), 0);	//阻塞
		if(ret > 0)
        {
            switch(allFlag)
            {
                case 1:
                    order++;
                    printf("%d:%s\n",order,receive);
                    break;
                case 2:
                    //printf("%s\n",receive);
                    write(fileid1,receive,strlen(receive)+1);
                    memset(receive,0,strlen(receive)+1);
                    break;
                case 3:
                    break;
                default:
                    break;

            }
  

            
            //printf("recv is %s\n", receive);
            //dealServerMessage(receive);

        }
	}
}
