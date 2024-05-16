/*******************************************************************************
 * Name        : minishell.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#define BLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define _POSIX_C_SOURCE 200809L // For sigaction
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>


// use gcc minishell.c -o minishell to test
// valgrind --leak-check=full ./minishell

//Done:
// How to include the hidden files // This is done 
// Why do i not see the other 200 items in lp // This is done

//Pending:
// How do i do the too many arguments becuase the way that I did it is not good. 
// Signaling control c thing also does not work // This kind of works but also fucked it remembers last function and only first command
// The echo does not print the seocnd item (rishi sucks) only prints rishi 
// You might need to use qsort(), but i think it always works

// CD valgrind is
// Interput is fucked

volatile sig_atomic_t interrupted = 0;

void lf(char* current_Dir){
    DIR* directory = opendir(current_Dir);
    
    if (directory == NULL){
        return;
    }

    struct dirent* read_directory;
    //struct stat fileinfo;

    while ((read_directory = readdir(directory)) != NULL){
        if (strcmp(read_directory->d_name, ".") == 0 || strcmp(read_directory->d_name, "..") == 0) {
            continue; // Skip current directory and parent directory entries
        }
        printf("%s\n", read_directory->d_name);
    }
    closedir(directory);
}

void lp() {
    DIR *proc_directory = opendir("/proc");

    if (proc_directory == NULL) {
        fprintf(stderr, "Error: Cannot open directory '/proc'. %s.\n", strerror(errno));
        return;
    }

    struct dirent *proccesses;
    while ((proccesses = readdir(proc_directory)) != NULL) {
        
        if (isdigit(*proccesses->d_name)) {
            
            char cmdline_path[PATH_MAX];
            snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", proccesses->d_name);

            FILE *command_line_input = fopen(cmdline_path, "r");
            if (command_line_input) {
                //printf("%s\n", proccesses->d_name); // This prints 1 2 3 and so one this is good but gets messed up after the if statment below
                char command[PATH_MAX];
                fgets(command, PATH_MAX, command_line_input);
                struct stat userstat;
                char fileName[1000];
                sprintf(fileName, "%s%s", "/proc/", proccesses->d_name);
                stat(fileName, &userstat);
                struct passwd *pw = getpwuid(userstat.st_uid);
                printf("%s %s %s\n", proccesses->d_name, pw->pw_name, command);
                fclose(command_line_input);
            }
        }
    }
    closedir(proc_directory);
}


void cd(char* user_dir){
    struct passwd *pwd = getpwuid(getuid());
    if (pwd == NULL) {
        fprintf(stderr, "Error: Cannot get passwd entry. %s.\n", strerror(errno));
        return;
    }
    // Maybe add a check to see if the dir is real or not first 
    //printf("I got this directory '%s' from the user\n", user_dir); // This prints 
    chdir(user_dir);
}

void handle_sigint(int sig) {
    interrupted = 1;
    printf("\n");
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
}

int main(){
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    // if (sigaction(SIGINT, &sa, NULL) == -1) {
    //     perror("sigaction");
    //     exit(EXIT_FAILURE);
    // }
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int running = 1;
    char* homeDir = getpwuid(getuid())->pw_dir;
    
    while(running){
        if (interrupted) {
            interrupted = 0;
            continue;
        }

        int i = 1;
        char user_input[1024] = {0};
        char full_path[PATH_MAX];
        char* user_command;
        char* argv[1024];
        int argc = 1;

        char* CWD;
        CWD = getcwd(NULL, 0); // Might have to free this later down the line

        if (CWD == NULL) {
            fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        
        printf("%s[%s]%s> ", BLUE, CWD, DEFAULT);
        

        //fgets(user_input, 1024, stdin); // Reads in the user input

        if (fgets(user_input, 1024, stdin) == NULL) {
            fprintf(stderr, "Error: Failed to read from stdin. %s.\n", strerror(errno));
            free(CWD);
            exit(EXIT_FAILURE);
        }
        //printf("Im cooked");
        char* token = strtok(user_input, " \n"); // Breaks down the input using both a space and a new line as delimerters if one of those occurs then it will add it to the array of argvs
        //printf("Im cooked");
        argv[0] = token; // Get the first input
        user_command = argv[0]; // This is essentially the user's command (what he or she wants to do)
        // while (token != NULL){ // We want to make sure the the item we have read is not null and the max number or of inputs we are expecting is 2 (so 0 and 1)
        //     token = strtok(NULL, " \n");
        //     argv[argc] = token;
        //     //printf("%s", token);
        //     argc++;
        //     //i++;
        // }
        while ((token = strtok(NULL, " \n"))   != NULL){ // We want to make sure the the item we have read is not null and the max number or of inputs we are expecting is 2 (so 0 and 1)
            argv[argc] = token;
            argc++;
            //i++;
        }
        argv[argc] = NULL;
        // for (int i = 0; i < argc; i++)
        //     printf("%s|", argv[i]);
        // printf("\n");
        
        if (argv[0] == NULL){
            free(CWD);
            continue;
        }

        //printf("%s", argv[3]);
        if (strcmp(user_command, "cd") == 0 && (argv[1] == NULL || (strcmp(argv[1], "~") == 0))){
            cd(homeDir); // This checks the case that the user just enters cd
            free(CWD);
            continue;
        }
        /*The reason that I need to make a list of arguments is because I 
        need to know how long it has to be so that I know when to use the 
        \n as a delimeter because that is the last input*/
        if (strcmp(user_command, "cd") == 0){
                if (argc > 2){
                fprintf(stderr, "Error: Too many arguments to cd.\n");
                free(CWD);
                continue;
                }
            // if (token[0] == '/') {
                // DIR* user_directory = opendir(token);
                if (argv[1][0] == '~'){
                    //printf("yo you entered a tilda"); // This prints just handle it correctly
                    
                    sprintf(full_path, "%s%s", homeDir, argv[1] + 1); // Appends the home dir to the dir with the ~ (homedir) and the rest of the dir that the user wants to switch into
                    
                    DIR* user_directory = opendir(full_path); // /home/ubuntu/Desktop
                    if (user_directory){
                        cd(full_path);
                    }
                    else{
                        fprintf(stderr, "Error: Cannot change directory to %s. %s.\n", full_path, strerror(errno));
                    }
                    //printf("%s\n", full_path);
                    cd(full_path);

                    free(CWD);
                    continue;
                }
                DIR* user_directory = opendir(argv[1]); // /home/ubuntu/Desktop
                if (user_directory){
                    cd(argv[1]);
                }
                else{
                    fprintf(stderr, "Error: Cannot change directory to %s. %s.\n", argv[1], strerror(errno));
                }
                closedir(user_directory);
                free(CWD);
                continue;
                // Valgrind is good 40
            // }
            //char* temp = argv[1];
            // if (argv[1][0] == '~'){
            //     //printf("yo you entered a tilda"); // This prints just handle it correctly
            //     sprintf(full_path, "%s%s", homeDir, argv[1] + 1); // Appends the home dir to the dir with the ~ and the rest of the dir that the user wants to switch into
            //     printf("%s\n", full_path);
            //     cd(full_path);
            //     free(CWD);
            //     continue;
            // }
            
            // sprintf(full_path, "%s/%s", CWD, argv[1]); // Appends the CWD to the dir that the user wants to switch into
            // // DIR* user_directory = opendir(full_path);
            // user_directory = opendir(full_path);
            // if (user_directory){
            //     cd(full_path); // This sends the full path into the cd function
            // }
            // else{
            //     fprintf(stderr, "Error: Cannot change directory to %s. %s.\n", argv[1], strerror(errno));
            // }

            // printf("Error: Too many arguments to cd.\n"); I don't know the condition where this would trigger but only when there is multiple inputs
        }
        else if (strcmp(user_command, "exit") == 0){
            running = 0; // Here we are changing the variable that is being checked in the while loop to 0 so that we can break out of the loop
            free(CWD);
            continue;
        }
        else if (strcmp(user_command, "pwd") == 0){
            printf("%s\n", CWD); // You might have to use DEFAULT but idk on change it only if the font color is weird 
            //also this should work because I don't think that the CWD or temp can be changed in between the calling of commands based on the user input
        }
        else if (strcmp(user_command, "lf") == 0){
            lf(CWD);
        }
        else if (strcmp(user_command, "lp") == 0){
            lp();
        }
        else {
            pid_t pid = fork();
            fflush(stdin);
            fflush(stdout);
            fflush(stderr);
            
            if (pid == -1) {
                fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
                // memset(user_input, 0, sizeof(user_input));
                // memset(full_path, 0, sizeof(full_path));
                // memset(argv, 0, sizeof(argv));
                exit(EXIT_FAILURE);

            } 
            else if (pid == 0) { // Child process
                execvp(user_command, argv);
                fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
                free(CWD);
                exit(EXIT_FAILURE);
            }
            else { // Parent process
                wait(NULL);
                wait(NULL);
            }
        }
        free(CWD);
    }
    
}