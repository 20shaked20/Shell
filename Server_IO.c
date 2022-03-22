#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

    struct sockaddr_in server_addr;
    int serv_sock;

    // opening the server socket.
    serv_sock = socket(AF_INET, SOCK_STREAM,0);
    if( serv_sock < 0 ) {
        printf("Socket creation failed, exiting method...\n");
        sleep(1);
        exit(1);

    }else{
        printf("Socket creation was a success..\n");
    }

    bzero(&server_addr, sizeof(server_addr)); // reset the buff.

    // enter ip,port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // local host
    server_addr.sin_port = htons(5555);
    
    // binding to establish connections.
    int con = connect(serv_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (con != 0){
        printf("failed to bind Socket..\n");
        sleep(1);
        exit(1);
    }else{
        printf("Socket binded successfuly..\n");
    }

    int listener = listen(serv_sock,1);
    if(listener != 0){
        printf("Listen to clients failed..\n");
        exit(1);
    }
    else{
        printf("Server is waiting for clients...\n");
    }
}