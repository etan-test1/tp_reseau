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
    struct sockaddr_in serv_addr, cli_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&cli_addr,0,sizeof(cli_addr));
    int sockfd;
    int receive=0;
    char rcv_msg[MAX_LEN];
    char send_msg[MAX_LEN] = "Luke : NON !!! CE N'EST PAS POSSIBLE ! CE N'EST PAS VRAI !";

    int queu_len = 5;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {stop("ERREUR LORS DE LA CREATION DE LA SOCKET");}
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( bind(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0 )
    {
        stop("ERREUR LORS DU BINDING :");
    }

    if(listen(sockfd, queu_len) < 0) stop ("ERREUR listen()");

    int clilen = sizeof(cli_addr);
    int newsockfd = accept (sockfd,&cli_addr,&clilen);
    

    if(newsockfd < 0) stop("ERREUR accept()");

    while (1)
    {
        bzero(&rcv_msg,MAX_LEN);
        int n = recv(newsockfd,rcv_msg,MAX_LEN,0);
        //rcv_msg[MAX_LEN-1] = "\0";
        if (n<0) stop("ERREUR recv()");
        printf("Message reçu : %s\n",rcv_msg);
        //n = send(newsockfd,send_msg,MAX_LEN,0);
        //if (n<0) stop("ERREUR send()");
    }
    
    close(newsockfd);
    close(sockfd);
}