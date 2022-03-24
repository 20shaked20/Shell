#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 9999
#define TRUE 1

int serv_sock; // so i can close it without problems.

void Display(int connect){

    char buff[MAX];
    
    while(TRUE) {

        bzero(buff, MAX);
   
        /* read the message from client and copy it in buffer */
        read(connect, buff, sizeof(buff));

        /* Prints the data the client requested */
        printf("%s\n",buff);

        /* in case we got Exit, return to main menu and stop recieving from the server, return to normal */
        if (strncmp("LOCAL", buff, 5) == 0) {
            close(serv_sock);
            exit(1);
        } 
    }

}

int main(){

    struct sockaddr_in server_addr;
    struct sockaddr_in cli_addr;
    int connect;

    /* Server socket creation */
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
    
    /* socket Bind */
    if (bind(serv_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))!= 0){
        printf("failed to bind Socket..\n");
        sleep(1);
        exit(1);
    }else{
        printf("Socket binded successfuly..\n");
    }

    /* listen */
    int listener = listen(serv_sock,1);
    if(listener != 0){
        printf("Listen to clients failed..\n");
        exit(1);
    }
    else{
        printf("Server is waiting for clients...\n");
    }

    /* connection */
    unsigned int len = sizeof(cli_addr);
    connect = accept(serv_sock, (struct sockaddr*)&cli_addr, &len);
    if(connect < 0){
        printf("Server failed to accept client...\n");
        exit(1);
    }else{
        printf("Server accpeted the client...\n");
    }

    Display(connect);
    close(serv_sock);
    exit(1);
}