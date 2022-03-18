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
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Welcome to Lior & Shaked Shell \n" );
    printf("Use with cautious! \n" );
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    // user handle :
    char* username = getenv("USER");
    printf("\n\n\n USER:@ %s", username);
    printf("\n");
    sleep(1);
    clear();

}

/**
 * @brief This method handles the user input we get, will be modified on the fly.
 * 
 * @param input user input.
 */
int user_input(char *input){

        char* read = NULL;
        
        // Exit shell case:
        if(strcmp(input,"EXIT") == 0){
            printf("Exiting shell, good bye ... ");
            sleep(1);
            exit(1);
        }
        // get directory case:
        if(strcmp(input,"pwd") == 0){
            get_curr_directory();
        }

        // handle echo msg case:
        // this line checks if a string starts with 'ECHO'
        read = strstr(input,"ECHO");
        if(strcmp(input,read) == 0){
            print_echo_msg(input);
        }

        // handle input.
        read = readline("\n ~");
        if(strlen(read) != 0) {
            add_history(read);
            strcpy(input,read);
            return 0;
        }else{
            return 1;
        }

}

/**
 * @brief Get the curr directory location.
 * the keyword to activate it - PWD.
 * 
 */
void get_curr_directory(){

    char curr_dir[2048];
    getcwd(curr_dir,sizeof(curr_dir));
    printf("\n %s",curr_dir);

}

/**
 * @brief This method prints an echo message.
 * 
 */
void print_echo_msg(char *echo){

    /** 
     * i forwad the pointer by 4.
     * this is because i have no need to see the 'ECHO' in reply.
     */

    echo+=4;
    printf("%s\n",*echo);
}

int main(){
    char *inputString ;
    inputString = (char*) malloc(100*sizeof(char));
    shell_initialize();

    while(1){

        if(user_input(inputString)){
            continue;
        }
    }
}