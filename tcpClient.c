#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char * receive[100]={0};
    char *p,*q;
    while(1)
    {
        printf(">>>");
        gets(receive);
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
            return 0;
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
    return 0;
}