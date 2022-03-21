/**
 * @file Shell.h
 * @author Shaked Levi, Lior Nagar
 * @brief This is the header file of the Shell.c program.
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H

/**
 * @brief This method is responsible for initliazing the shell at startup.
 * 
 */
void shell_initialize();

/**
 * @brief This method handles the user input we get, will be modified on the fly.
 * 
 * @param input user input.
 */
void user_input(char *input);

/**
 * @brief Get the curr directory location.
 * the keyword to activate it - PWD.
 * 
 */
void get_curr_directory();

/**
 * @brief This method prints an echo message.
 * 
 */
void print_echo_msg(char *echo);

/**
 * @brief This method opens a tcp socket to the localhost.
 * the user operates as the client in our case.
 * 
 */
void open_tcp_socket();

#endif //SHELL_SHELL_H