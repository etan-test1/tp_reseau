//n1.c aka UDPSERVER.C
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

void ajouter_client(){

}

int main(void){

    printf("je suis SVPN, j'écouterai l'UDP sur 1203\n");
    
    //Socket UDP IPv4
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        stop("socket creation failed");
    }

    //Structure d'adresse
    struct sockaddr_in svpnaddr, clientaddr, *listeclients;
    memset(&svpnaddr, 0, sizeof(svpnaddr));
    memset(&clientaddr, 0, sizeof(clientaddr));
    //Information de SVPN
    svpnaddr.sin_family = AF_INET;
    svpnaddr.sin_port = htons(1203);
    if (inet_aton("127.0.0.1" , &svpnaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}
    //Informations des clients / Liste de max 10 clients
    listeclients=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)*10);

    //Association socket adresse avec bind()
    if(bind(sockfd,(const struct sockaddr *)&svpnaddr,sizeof(svpnaddr))<0){
        stop("bind failed");
    }
    printf("socket d'écoute bind correctement\n");

    //Boucle infinie
    int n, len; int MAXLINE = 1024;
    char buffer[MAXLINE];
    char* reponse = "entendu";
    while(1){
        //Attend recept message
        printf("attend la réception d'un message\n");
        n = recvfrom(sockfd, (char*)buffer, MAXLINE,
        MSG_WAITALL,(struct sockaddr *)&clientaddr,&len);
        //Affiche message reçu
        buffer[n]='\0';
        printf("A client said : %s\n",buffer);
        //Ajout du client à la liste
        
        //Réponse au client
        sendto(sockfd, (const char *)reponse, strlen(reponse), MSG_CONFIRM,
        (const struct sockaddr *)&clientaddr, len);
        //Sleep 1 sec
        sleep(1);
    }
    return EXIT_SUCCESS;
}