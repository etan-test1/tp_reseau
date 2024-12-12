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

#define PORT_ME 1201
#define PORT_SERV 1202
#define MAX_LEN 2048

typedef struct cli {
    char* name;
    int sockfd;
} cli;

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
    int sockfd_as_serv, sockfd_as_cli;
    int receive=0;
    char rcv_msg[MAX_LEN];
    char send_msg[MAX_LEN];

    int queu_len = 5;

    sockfd_as_serv = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_as_serv == -1) {stop("ERREUR LORS DE LA CREATION DE LA SOCKET");}
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_port = htons(PORT_ME);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    struct sockaddr_in another_serv_addr;
    memset(&another_serv_addr,0,sizeof(another_serv_addr));

    sockfd_as_cli = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_as_cli == -1) {stop("ERREUR LORS DE LA CREATION DE LA SOCKET");}
    another_serv_addr.sin_family = AF_INET ;
    another_serv_addr.sin_port = htons(PORT_SERV);
    another_serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if ( bind(sockfd_as_serv,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0 )
    {
        stop("ERREUR LORS DU BINDING :");
    }

    if(listen(sockfd_as_serv, queu_len) < 0) stop ("ERREUR listen()");

    int clilen = sizeof(cli_addr);
    int newsockfd = accept (sockfd_as_serv,&cli_addr,&clilen);
    

    if(newsockfd < 0) stop("ERREUR accept()");

    while (1)
    {
        bzero(&rcv_msg,MAX_LEN);
        int n = recv(newsockfd,rcv_msg,MAX_LEN,0);
        if (n<0) stop("ERREUR recv()");
        /*
        if (rcv_msg[0] == "N" && (rcv_msg[1] == "1" || rcv_msg[1] == "2" || rcv_msg[1]=="3" || rcv_msg[1]=="4") && strlen(rcv_msg)==2)
        {
            if (connect(sockfd_as_cli, &another_serv_addr, sizeof(another_serv_addr)) < 0) stop ("ERREUR connect()");
            {
                send(sockfd_as_cli,rcv_msg,3,0);
            }   
        }

        else if (rcv_msg[0] =="F" && rcv_msg[1]=="F" && rcv_msg[2]=="F" && strlen(rcv_msg)==3) //Début de transfert fichier
        {

        }
        else
        {}
        */
        printf("Message reçu : %s\n",rcv_msg);
        //n = send(newsockfd,send_msg,MAX_LEN,0);
        //if (n<0) stop("ERREUR send()");
    }
    
    close(newsockfd);
    close(sockfd_as_serv);
}