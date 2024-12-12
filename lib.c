#include <stdio.h>
#include <string.h>


int compt_char_file (char* path) // Le fichier ne doit pas être ouvert quand on appelle cette fonction.
{
    int compteur = 0;
    FILE * file;
 
    /* ouverture du fichier */
    if ((file = fopen(path, "r")) == NULL) perror("Erreur à l'ouverture du fichier");
 
    else {
        /* parcours du fichier */
        while(fgetc(file) != EOF)
        compteur ++; /* incrémentation du compteur */
    }
 
    printf("Le nombre de caractères du fichier est de : %d\n", compteur);
 
    /* fermeture du fichier */
    fclose(file);
}

FILE * ouverture_file (char* path,char* mode) 
{
    FILE * file;
    if ((file = fopen(path, mode)) == NULL) perror("Erreur à l'ouverture du fichier");
    return file;
}


int file_cpy_n_char (FILE * file, int n_char, char* buf, int buffsize)
{
    int compt;
    bzero(buf,buffsize + 1 );
    for (compt = 0; compt < n_char ; compt ++)
    {
        buf[compt] = fgetc(file);
    }
    return compt +1;
}

void send_msg_n (int sockfd, const char* msg, int len, int buffsize)
{
    int n;
    int i = 0;
    int compt = 0;
    int curseur = 0;
    if (buffsize>len) {
        send(sockfd,msg,len,0);
        }

    else {
        char* cpy[buffsize];
        for (compt = 0 ; (compt<len); )
            {
                bzero(cpy,buffsize);
                for (i = 0; (i < buffsize)  && (compt < len); i++, compt ++ )
                {
                    //printf("%c \n", msg[compt]);
                    //cpy[i] = msg[compt];
                    //printf("%c \n", cpy[i]);
                    //printf("%s \n", cpy);
                }
                strncat(cpy,msg+curseur,i);
                printf("i+1 = %d \n",i+1);
                printf("%s\n",cpy);
                curseur = curseur + i;
                n = send(sockfd,cpy,i+1,0);
                if (n<0){perror("Erreur lors de l'envoie");}
        }
        }
    

}

/*
int main (int argc, char** argv )
{

    char cpy [20];
    char * text = "C'est un texte et je dois le copier";

    int i;
    for(i=0; i<20; i++)
    {
        cpy[i] = text[i];
    }
    printf("%s \n",cpy);
    printf("%s \n",text);
}
*/