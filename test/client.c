#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXSEND 256         // send to server
#define MAXRECEIVE 256      // receive from server

int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    // Socket Connection

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8700);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error\n");
    }


    //Send a message to server
    // char message[] = {"Hi there"};
    char message[MAXSEND];
    while(1){
        
        char receiveMessage[MAXRECEIVE] = {};
        send(sockfd,message,sizeof(message),0);
        /* stop here and wait receive */
        recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        printf("%s",receiveMessage);
        printf("Input Something\n");
        memset(message, '\0', sizeof(message));
        scanf("%s", message);
    }
    printf("close Socket\n");
    close(sockfd);
    
    return 0;
}