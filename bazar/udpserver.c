//UDPSERVER.C
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
    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    //Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);
    //servaddr.sin_addr.s_addr = "127.0.0.1";
    if (inet_aton("127.0.0.1" , &servaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}

    //Association socket adresse avec bind()
    if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        stop("bind failed");
    }

    //Boucle infinie
    int len, n; int MAXLINE = 1024;
    char buffer[MAXLINE];
    char *hello = "PONG";
    while(1){
        //Attend recept message
        n = recvfrom(sockfd, (char*)buffer, MAXLINE,
        MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
        //Affiche message reçu
        buffer[n]='\0';
        printf("Client : %s\n",buffer);
        //Affiche l'ip et le port de l'emetteur
        printf("Client IP : %s\n",inet_ntoa(cliaddr.sin_addr));
        printf("Client PORT : %d\n",ntohs(cliaddr.sin_port));
        //Sleep 1 sec
        sleep(1);
        //Envoie le message PONG
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
        (const struct sockaddr *)&cliaddr, len);
        printf("Hello message sent.\n");
    }
    return EXIT_SUCCESS;
}