//UDPCLIENT.C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void stop(char* message){
    perror(message);
    exit(EXIT_FAILURE);
}

int main(void){

    //Socket UDP IPv4
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        stop("socket creation failed");
    }

    //Structure d'adresse pour 127.0.0.1 port 1234
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    //Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);
    //servaddr.sin_addr.s_addr = "127.0.0.1";
    if (inet_aton("127.0.0.1" , &servaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}

    //Boucle infinie
    int len, n; int MAXLINE = 1024;
    char buffer[MAXLINE];
    char *hello = "PING";
    while(1){
        //Envoie le message PING
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
        (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("PING sent.\n");
        //Wait till message reception
        n = recvfrom(sockfd, (char*)buffer, MAXLINE,
        MSG_WAITALL,(struct sockaddr *)&servaddr,&len);
        //Affiche message reçu
        buffer[n]='\0';
        printf("Server : %s\n",buffer);
    }
    return EXIT_SUCCESS;
}