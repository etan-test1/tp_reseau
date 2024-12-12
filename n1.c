//n1.c
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

    printf("je suis N1, j'écouterai sur 1204\n");
    
    //Fichier associé à N1
    char* file_name = "info1.txt";

    //Socket UDP IPv4
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        stop("socket creation failed");
    }

    //Information de SVPN
    struct sockaddr_in svpnaddr; //serv c'est moi client c'est l'autre
    memset(&svpnaddr, 0, sizeof(svpnaddr));
    svpnaddr.sin_family = AF_INET;
    svpnaddr.sin_port = htons(1203);
    if (inet_aton("127.0.0.1" , &svpnaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}
/*
    //Association socket adresse avec bind()
    if(bind(sockfd,(const struct sockaddr *)&svpnaddr,sizeof(svpnaddr))<0){
        stop("bind failed");
    }
    printf("socket d'écoute bind correctement\n");
*/
    //Envoie un message au SVPN pour se faire connaître
    int len;
    char *hello = "je suis N1, j'écouterai sur 1204";
    if(sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM,
    (const struct sockaddr *)&svpnaddr, sizeof(svpnaddr))<0){stop("problème message");}
    printf("Message de départ envoyé.\n");

    //Boucle infinie
    int n; int MAXLINE = 1024;
    char buffer[MAXLINE];
    while(1){
        //Attend recept message
        printf("attend la réception d'un message\n");
        n = recvfrom(sockfd, (char*)buffer, MAXLINE,
        MSG_WAITALL,(struct sockaddr *)&svpnaddr,&len);
        //Affiche message reçu
        buffer[n]='\0';
        printf("SVPN said : %s\n",buffer);
        //Sleep 1 sec
        sleep(1);
    }
    return EXIT_SUCCESS;
}