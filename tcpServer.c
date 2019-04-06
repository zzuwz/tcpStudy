#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include<pthread.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH "/home/wz1026/program/tcpAPP/sharedDir/"
int fileid1;
int allFlag =0;

int dealRecv(char* receive,int fd);
void *recv_fun(void *p)
{
	int fd; 
	int *q = p;
	fd  = *q;		//fd = *((int *)p);
	char buf[1024] = { 0 };
	while(1)
	{
		if(recv(fd, buf, sizeof(buf), 0) <= 0)
			return 0;
        dealRecv(buf,fd);
		//printf("recv is %s\n", buf);
		//send(fd, buf, sizeof(buf), 0);    
	}
}
int main(int argc, char *argv[])
{	
	pthread_t id;
	char buf[1024] = { 0 };
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
	char listFlag[1024]={"0"};
	char pwd[1024]={PATH};
	if(allFlag==3)
	{
		if(strcmp(receive,"receiveOk")==0)
		{
			allFlag=0;
		}

			
		write(fileid1,receive,strlen(receive)+1);
		memset(receive,0,sizeof(receive));

	}
	else
	
		{
			
		
		
		if(strcmp(receive,"quit")==0)
		{
			printf("一个客户端成功退出\n"); 
			pthread_exit((void*)1);            
		}
		else if(strcmp(receive,"list")==0)
		{
			printf("客户端请求获取文件列表\n");

			DIR *dp;  //定义一个结构体变量
			dp = opendir(PATH);

			struct dirent *ep;   //用来保存一个文件
			ep = readdir(dp);    //readdir,从目录中读出一个文件
			while( ep != NULL)
			{
				if(ep->d_name[0] != '.')	//以.开头是隐藏文件，不显示
				{
					printf("file name is %s\n", ep->d_name);   //d_name 文件名
					//strcpy(listFlag+1,ep->d_name);
					//printf("记录的是%s\n",listFlag);
					send(fd, ep->d_name, strlen(ep->d_name)+1, 0);								
				}

				ep = readdir(dp);
			}
			//send(fd,"listOk",sizeof("listOk"),0);
		}
		else
		{
			p=strtok(receive," ");
			q=strtok(NULL," ");       //将字符串分割
			if(strcmp(p,"get")==0)
			{
				printf("客户端请求下载文件:%s\n",q);
				int len;
				strcat(pwd,q);
				//printf("%s\n",pwd);
				int fileid = open(pwd, O_RDONLY);
				if(fileid>0)
				{
					char fileBuf[1024] = { 0 };
					while((len = read(fileid, fileBuf, sizeof(fileBuf))) > 0)
					{
						send(fd,fileBuf,len,0);
						memset(fileBuf, 0, strlen(fileBuf)+1);
					}
					close(fileid);
				}


			}
			else if(strcmp(p,"put")==0)
			{
				printf("客户端将要上传文件:%s\n",q);
				strcat(pwd,q);
				fileid1=open(pwd,O_RDWR | O_CREAT | O_TRUNC, 0666);
				allFlag=3;
			}
		}
	}
}