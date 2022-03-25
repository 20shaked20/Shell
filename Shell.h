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

/**
 * @brief This methods shows the current library files.
 * 
 */
void show_library_files();

/**
 * @brief This method is used to change the current directory.
 * @param chdir() -> this command is a system call.
 */
void change_directory(char *cd_input);

/**
 * @brief This method copies a file in this way : COPY SRC DST
 * @SRC -> the file source we copy
 * @DST -> the copied file location
 * @param fopen() -> part of the C library, it is implmeneted by calling open() which is a system call 
 * @param fread() -> part of the C library, it is implmeneted by calling read() which is a system call 
 * @param fwrite() -> part of the C library, it is implmeneted by calling write() which is a system call 
 */
void copy_from_src_to_dst(char *copy_input);

/**
 * @brief This method delets a file : DELETE FILENAME
 * @param unlink() -> is a system call.
 */
void delete_file(char *delete_input);

void split(char *input);
void manual_system_calls(char *input);
#endif //SHELL_SHELL_H