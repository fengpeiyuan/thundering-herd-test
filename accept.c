#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>

#define SERV_PORT  19999

int main(int argc,char **argv)
{
     int listenfd,connfd;
     pid_t  childpid,childpid2;
     socklen_t clilen;
     struct sockaddr_in cliaddr,servaddr;
    
     listenfd = socket(AF_INET,SOCK_STREAM,0);
     bzero(&servaddr,sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
     servaddr.sin_port = htons (SERV_PORT);

     bind(listenfd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
     
     listen(listenfd,1000);

     clilen = sizeof(cliaddr);

     if( (childpid = fork()) == 0)
     {
         while(1)
         {
             connfd = accept(listenfd,(struct sockaddr *) &cliaddr,&clilen);
             printf("fork 1 is [%d],error is %m\n",connfd);

         }
     }

     if( (childpid2 = fork()) == 0)
     {
         while(1){
             connfd = accept(listenfd,(struct sockaddr *) &cliaddr,&clilen);
             printf("fork 2 is [%d]，error is %m\n",connfd);
         }
     }

     sleep(100);

     return 1;

}


