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

#include <dirent.h> // for directory files 


#include "Shell.h"

// method to clear the shell.
#define clear() printf("\033[H\033[J]")
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define WHITE "\033[0m"

int cli_sock; // global for use when closing or opening the socket.

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
    sleep(3); // TODO: make a bind to enter, in order to acess shell.
    clear();

}


void user_input(char *input){

        // Exit shell case:
        if(strcmp(input,"EXIT") == 0){
            printf("Exiting shell, good bye ...\n");
            sleep(1);
            exit(1);
        }
        // get directory case:
        if(strcmp(input,"pwd") == 0){
            get_curr_directory();
            printf("\n");
            return;
        }
        
        // open a tcp localhost, we are client.
        if(strcmp(input,"TCP PORT") == 0){
            open_tcp_socket();
            dup2(1,1234);
            dup2(cli_sock,1);
            return;
        }

        // close the client socket.
        if(strcmp(input,"LOCAL") == 0){
            close(cli_sock);
            dup2(1234,1);
            return;
        }

        if(strcmp(input,"DIR") == 0){
            show_library_files();
            return;
        }

        //handle cd case:
        //this line checks if a string starts with 'CD'
        if(strncmp(input,"CD",2) == 0){
            change_directory(input);
            return;
        }
        
        //handle copy case:
        //this line checks if a string starts with 'COPY'
        if(strncmp(input,"COPY",4) == 0){
            copy_from_src_to_dst(input);
            return;
        }

        // handle echo msg case:
        // this line checks if a string starts with 'ECHO'
        if(strncmp(input,"ECHO",4) == 0){
            print_echo_msg(input);
            return;
        }

        // handle delete file case:
        // this line checks if a string starts with 'DELETE'
        if(strncmp(input,"DELETE",6) == 0){
            delete_file(input);
            return;
        }

        /**
         * @brief in case everything else is not accsesed, we will invoke system calls.
         *  system is a 'library method' which invokes the desired system call given the input.
         */
        system(input);
        return;
        
}

void delete_file(char *delete_input){
    /** 
     * i forwad the pointer by 7.
     * this is because i do not need substring 'DELETE'.
     */
    delete_input+=7;
    unlink(delete_input);
}

void copy_from_src_to_dst(char *copy_input){
    /** 
     * i forwad the pointer by 5.
     * this is because i do not need substring 'COPY'.
     */
    copy_input+=5;

    // extract the src location.
    char *src, *handle_src;
    src = (char*)malloc(sizeof(char)*256);
    handle_src = src;
    if(src == NULL){
        printf("Memory allocation failed for src");
    }
    while(*copy_input != ' '){
        *handle_src = *copy_input;
        handle_src++;
        copy_input++;
    }
    *handle_src = '\0';

    copy_input++; // skip the ' ' 

    // extract the dst location
    char *dst, *handle_dst;
    dst = (char*)malloc(sizeof(char)*256);
    handle_dst = dst;
    if(dst == NULL){
        printf("Memory allocation failed for src");
    }
    
    while(*copy_input != '\0'){
        *handle_dst = *copy_input;
        handle_dst++;
        copy_input++;
    }
    *handle_dst = '\0';
    printf("%s\n",src);
    printf("%s\n",dst);
    // Copying the file:
    size_t size;
    char buf[BUFSIZ];
    FILE *src_file = fopen(src,"r");
    if(src_file == NULL){
        printf("Failed to open src file..\n");
        return;
    }
    FILE *dst_file = fopen(dst,"w");
    if(dst_file == NULL){
        printf("Failed to open dest file..\n");
        return;
    }

//COPY /home/shaked/Desktop/OS-Course/Shell/Txt /home/shaked/Desktop/OS-Course/Shell/Txt2 

    //reading and writing to the new file.
    size = fread(buf, 1, BUFSIZ, src_file);
    while (size > 0) {
        fwrite(buf, 1, size, dst_file);
        size = fread(buf, 1, BUFSIZ, src_file);
    }

    fclose(src_file);
    fclose(dst_file);

}

void change_directory(char *cd_input){
    /** 
     * i forwad the pointer by 3.
     * this is because i do not need substring 'cd'.
     */
    cd_input+=3;
    if(chdir(cd_input) != 0){
        printf("cd: no such file or directory: %s\n",cd_input);
    }
}


void show_library_files(){

    DIR *folder_contents;
    struct dirent *file_name;
    int idx = 1;


    folder_contents = opendir(".");
    if(folder_contents == NULL){
        printf("Unable to read from directory");
        return;
    }else{
        while( (file_name = readdir(folder_contents))){
            printf("%s ",file_name->d_name);
            idx++;
        }
        printf("\n");
    }

    closedir(folder_contents);
    return;

}

void open_tcp_socket(){

    struct sockaddr_in server_addr;

    // opening the client socket.
    cli_sock = socket(AF_INET, SOCK_STREAM,0);
    if( cli_sock < 0 ) {
        printf("Socket creation failed, exiting method...\n");
        sleep(1);
        // clear();
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
        // clear();
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
    printf("%s",curr_dir);
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

        printf(GREEN); // change color to green
        printf("%s",getenv("USER")); // username.
        printf("@ubuntu"); // os 
        printf(WHITE); // changes to the basic color.
        printf(":");
        printf(PURPLE); // change color to purple
        printf("~");
        get_curr_directory(); //directory
        printf("$ ");

        printf(WHITE); // changes to the basic color.
        //using fgets so it will include spaces, etc..
        fgets(inputString,100,stdin);
        inputString[strcspn(inputString,"\n")] = 0;
        user_input(inputString);
    }
}