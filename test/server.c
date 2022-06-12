#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MAXSEND 256             // send to client
#define MAXRECEIVE 256          // receive from client

int main(int argc , char *argv[])

{
    //  Create Socket
    char inputBuffer[MAXRECEIVE] = {};
    char message[] = {"Connection established!\n"};
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    // Socket Connection
    struct sockaddr_in serverInfo,clientInfo;   // clentInfo stored the information from client
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;    // AF_INET = Address Family , PF_INET = Protocol Family
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    listen(sockfd,100);
    
    forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
    int creat_connection = 0;
    char rep_message[] = {"You send: "};
    while(1){
        char reply[MAXSEND];
        // send(forClientSockfd, inputBuffer,sizeof(inputBuffer) , 0);
        /* stop here and wait the receive */
        memset(inputBuffer, '\0', sizeof(inputBuffer));
        recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);

        /* wait receive and concat the replyment */
        memset(reply, '\0', sizeof(reply));
        strcat(reply, rep_message);
        strcat(reply, inputBuffer);
        strcat(reply, "\n");
        /* ======================== */
        creat_connection ? send(forClientSockfd, reply,sizeof(reply),0) : send(forClientSockfd, message, sizeof(message), 0);
        if(creat_connection)
            printf("Get:%s\n",inputBuffer);

        creat_connection = 1;
    }
    return 0;
}