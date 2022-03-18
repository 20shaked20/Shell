#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "Shell.h"

// method to clear the shell.
#define clear() printf("\033[H\033[J]")

/**
 * @brief This method is responsible for initliazing the shell at startup.
 * 
 */
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

/**
 * @brief This method handles the user input we get, will be modified on the fly.
 * 
 * @param input user input.
 */
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

/**
 * @brief Get the curr directory location.
 * the keyword to activate it - PWD.
 * 
 */
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

/**
 * @brief This method prints an echo message.
 * 
 */
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