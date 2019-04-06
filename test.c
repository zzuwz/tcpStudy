#include<string.h>
#include<stdio.h>

#include <sys/stat.h>
#include <dirent.h>

 #define PATH "/home/wz1026/program/tcpAPP/sharedDir"
int main(void)
{
/*    char input[16]="abc,d";
    char*p;
    /*strtok places a NULL terminator
    infront of the token,if found*/
/*    p=strtok(input,",");
    if(p)
        printf("%s\n",p);
        /*Asecond call to strtok using a NULL
        as the first parameter returns a pointer
        to the character following the token*/
/*    p=strtok(NULL,",");
    if(p)
        printf("%s\n",p);*/
  
 /*     char buf[100]={"list"};
      char buf1[100]={"0"};
      strcpy(buf1+1,buf);
      //char buf2[100]={0};
      //strcat(buf1,buf);
  //gets(buf);
    printf("%s is %d,%d\n",buf1,sizeof(buf1),strlen(buf1)+1);*/
  /*DIR *dp;  //定义一个结构体变量
	dp = opendir("/home/wz1026/program/tcpAPP/sharedDir");

	struct dirent *ep;   //用来保存一个文件
	ep = readdir(dp);    //readdir,从目录中读出一个文件

	while( ep != NULL)
	{
		if(ep->d_name[0] != '.')	//以.开头是隐藏文件，不显示
		{
			printf("file name is %s\n", ep->d_name);   //d_name 文件名
		}
		ep = readdir(dp);
	}*/
  // int i=0;
  // while(1)
  // {

  // }
      printf("%s\n",PATH);
      return 0;
 
}

