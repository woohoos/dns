#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define BUFFLEN 1024

int main(int argc, char *argv[]){
    WSADATA data;
    int sock;
    struct hostent *hp;
    struct sockaddr_in servaddr;
    char buffer[BUFFLEN];

    if (argc != 3){
        printf("Naudojimas: %s <hostname> <port>\n",argv[0]);
        return -1;
    }

    WSAStartup(MAKEWORD(2,2),&data);
    hp = gethostbyname(argv[1]);
    sock = socket(AF_INET, SOCK_STREAM,0);
    memset(&servaddr,0,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    memcpy((char *)&servaddr.sin_addr, hp->h_addr, hp->h_length);
    connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr));

    memset(&buffer,0,BUFFLEN);
    printf("Iveskite zinute: ");
    fgets(buffer, BUFFLEN-4, stdin);
    strcat(buffer,"\r\n\r\n");
    send(sock,buffer,strlen(buffer),0);
    memset(&buffer,0,BUFFLEN);
    recv(sock,buffer,BUFFLEN,0);
    printf("Serveris atsiunte: %s\n", buffer);
    closesocket(sock);
    return 0;
}
