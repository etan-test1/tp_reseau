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

#define PORT 1234
#define MAX_LEN 2048

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
    char send_msg[MAX_LEN] = "DARK VADOR : LUKE, JE SUIS TON PERE .";


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {stop("ERREUR LORS DE LA CREATION DE LA SOCKET");}
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0) stop ("ERREUR connect()");


    //while (1)
    //{
        
        int n = send(sockfd,send_msg,MAX_LEN,0);
        if (n<0) stop("ERREUR send()");
		bzero(&rcv_msg,MAX_LEN);

        n = recv(sockfd,rcv_msg,MAX_LEN,0);
        //rcv_msg[MAX_LEN-1] = "\0";
        if (n<0) stop("ERREUR recv()");
        printf("Message reçu : %s\n",rcv_msg);
    //}
    close(sockfd);
}