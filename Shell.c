/**
 * @file Shell.c
 * @author Shaked Levi, Lior Nagar
 * @brief This program is a Shell project, it will have some basic options like the shell does.
 * includes -> pwd,ls,cd ..., for further details ,enter the "Help" keyword in the program.
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>


#include "Shell.h"

// method to clear the shell.
#define clear() printf("\033[H\033[J]")


void shell_initialize(){
    clear();
    
    // user greetings : 
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Welcome to Lior & Shaked Shell \n" );
    printf("Use with cautious! \n" );
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // user handle :
    char* username = getenv("USER");
    printf("\n\n\nUSER:@%s", username);
    printf("\n");
    sleep(1);
    clear();

}


void user_input(char *input){

        // Exit shell case:
        if(strcmp(input,"EXIT\n") == 0){
            printf("Exiting shell, good bye ...");
            sleep(1);
            exit(1);
        }
        // get directory case:
        if(strcmp(input,"pwd\n") == 0){
            get_curr_directory();
            return;
        }
        
        // open a tcp localhost, we are client.
        if(strcmp(input,"TCP PORT\n") == 0){
            open_tcp_socket();
            return;
        }

        // handle echo msg case:
        // this line checks if a string starts with 'ECHO'
        char echo[5];
        strncpy(echo,&input[0],4);
        echo[4] = '\0';
        if(strcmp(echo,"ECHO") == 0){
            print_echo_msg(input);
            return;
        }
        
}
void open_tcp_socket(){

    int cli_sock;
    struct sockaddr_in server_addr;

    // opening the client socket.
    cli_sock = socket(AF_INET, SOCK_STREAM,0);
    if( cli_sock < 0 ) {
        printf("Socket creation failed, exiting method...\n");
        sleep(1);
        clear();
        return; // maybe use exit(1)

    }else{
        printf("Socket creation was a success..\n");
    }

    bzero(&server_addr, sizeof(server_addr)); // reset the buff.

    // enter ip,port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); // local host
    server_addr.sin_port = htons(5555);
    
    // trying to establish connections.
    int con = connect(cli_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (con != 0){
        printf("Connection with server failed, exiting method...\n");
        sleep(1);
        clear();
        return; // maybe use exit(1)
    }else{
        printf("Connection with the server was a success..\n");
    }


}

void get_curr_directory(){

    long size;
    char *buf;
    char *curr_dir;
    size = pathconf(".",_PC_PATH_MAX);
    if((buf = (char*)malloc((size_t)size))!=NULL){
        curr_dir = getcwd(buf,(size_t)size);
    }
    printf("%s\n",curr_dir);
}


void print_echo_msg(char *return_echo){

    /** 
     * i forwad the pointer by 4.
     * this is because i have no need to see the 'ECHO' in reply.
     */
    return_echo+=5;
    printf("%s",return_echo);
}

int main(){
    char *inputString ;
    inputString = (char*) malloc(100*sizeof(char));
    shell_initialize();
    
    while(1){
        //using fgets so it will include spaces, etc..
        // to put in mind.> dont forget the use of \n when checking for inputs!.
        fgets(inputString,100,stdin);
        user_input(inputString);
    }
}