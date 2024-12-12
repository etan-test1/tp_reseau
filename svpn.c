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

int main(void){

    printf("je suis SVPN, j'écouterai l'UDP sur 1203, le TCP sur 1202\n");
    
    //PARTIE UDP
    //Socket UDP IPv4
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0){
        stop("socket creation failed");
    }

    //Structure d'adresse
    struct sockaddr_in svpnaddr, clientudpaddr, *listeclients;
    memset(&svpnaddr, 0, sizeof(svpnaddr));
    memset(&clientudpaddr, 0, sizeof(clientudpaddr));
    //Information de SVPN
    svpnaddr.sin_family = AF_INET;
    svpnaddr.sin_port = htons(1203);
    if (inet_aton("127.0.0.1" , &svpnaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}
    //Informations des clients / Liste de max 3 clients udp
    listeclients=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in)*3);
    int nbclients = 0;

    //Association socket adresse avec bind()
    if(bind(sockfd,(const struct sockaddr *)&svpnaddr,sizeof(svpnaddr))<0){
        stop("bind failed");
    }
    printf("socket udp bind correctement\n");


    //PARTIE TCP : Serveur TCP
    //Socket TCP IPv4
    int socktcpfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socktcpfd<0){
        stop("socket creation failed");
    }
    else{printf("socket tcp creation success\n");}
    //Structure d'adresse pour 127.0.0.1 port 1202
    struct sockaddr_in svpntcpaddr, cvpnaddr;
    memset(&svpntcpaddr, 0, sizeof(svpntcpaddr));
    memset(&cvpnaddr, 0, sizeof(cvpnaddr));
    //Server information
    svpntcpaddr.sin_family = AF_INET;
    svpntcpaddr.sin_port = htons(1202);
    //servaddr.sin_addr.s_addr = "127.0.0.1";
    if (inet_aton("127.0.0.1" , &svpntcpaddr.sin_addr) == 0) 
	{stop("inet_aton failed");}
    //Association socket adresse avec bind()
    if(bind(socktcpfd,(const struct sockaddr *)&svpntcpaddr,sizeof(svpntcpaddr))<0){
        stop("socket bind failed");
    }
    else{printf("socket tcp successfully binded\n");}
    //Ecoute d'un client (client VPN)
    if((listen(socktcpfd,1))!=0){
        exit("listen failed");
    }
    else{printf("server listening for tcp\n");}
    int lentcp = sizeof(cvpnaddr);
    //Accepte un client
    int connfd = accept(socktcpfd, (struct sockaddr_in*)&cvpnaddr,&lentcp);
    if (connfd<0){
        printf("server accept failed\n");
        exit(0);
    }
    else{printf("server accepted the tcp client\n");}


    //BOUCLE INFINIE
    int n, len; int MAXLINE = 1024; int i,check;
    char buffer[MAXLINE];
    char* reponse = "entendu";
    while(1){
        //Attend recept message
        printf("attend la réception d'un message udp\n");
        n = recvfrom(sockfd, (char*)buffer, MAXLINE,
        MSG_WAITALL,(struct sockaddr *)&clientudpaddr,&len);
        //Affiche message reçu
        buffer[n]='\0';
        printf("A client said : %s\n",buffer);
        //Ajout du client à la liste :
            //Recherche du client dans la liste
            //Ajout si hors de la liste
        //Réponse au client
        sendto(sockfd, (const char *)reponse, strlen(reponse), MSG_CONFIRM,
        (const struct sockaddr *)&clientudpaddr, len);
        //Sleep 1 sec
        sleep(1);
    }
    return EXIT_SUCCESS;
}