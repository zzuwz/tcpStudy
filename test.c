#include<string.h>
#include<stdio.h>
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
  
      char buf[100]={0};
  gets(buf);
    printf("%s is %d,%d\n",buf,sizeof(buf),strlen(buf)+1);
      return 0;
 
}

