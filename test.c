#include<stdint.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<time.h>
#include<arpa/inet.h>

#include "lib.h"

#define PORT 1234
#define MAX_LEN 20

void stop(char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main (int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    int sockfd;
    int receive=0;
    char rcv_msg[MAX_LEN];
    char* send_msg = "DARK VADOR : LUKE, JE SUIS TON PERE .";
    int len_msg = strlen(send_msg);


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {stop("ERREUR LORS DE LA CREATION DE LA SOCKET");}
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0) stop ("ERREUR connect()");


    //while (1)
    //{
        
        send_msg_n(sockfd,send_msg,len_msg,MAX_LEN);


    //}
    close(sockfd);
}