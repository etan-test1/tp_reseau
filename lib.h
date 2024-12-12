#include <stdio.h>
#ifndef LIB_H
#define LIB_H

typedef struct request{
    const char * name;
    const char * path;

}request;

int compt_char_file (char* path);
FILE * ouverture_file (char* path,char* mode);
int file_cpy_n_char (FILE * file, int n_char, char* buf,int buffsize);//
void send_msg_n (int sockfd, char* msg, int len, int buffsize);

#endif