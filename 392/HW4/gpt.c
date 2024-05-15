/*******************************************************************************
 * Name        : minishell.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#define _POSIX_C_SOURCE 200809L // For sigaction
#define _GNU_SOURCE // For get_current_dir_name
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h> // Added for isdigit()

#define BLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"

volatile sig_atomic_t interrupted = 0;

void handle_sigint(int sig) {
    interrupted = 1;
}

void lf(const char *current_dir) {
    DIR *directory = opendir(current_dir);
    if (directory == NULL) {
        fprintf("Error: Cannot open directory '%s'. %s.\n", current_dir, strerror(errno));
        return;
    }

    struct dirent *read_directory;
    while ((read_directory = readdir(directory)) != NULL) {
        if (strcmp(read_directory->d_name, ".") == 0 || strcmp(read_directory->d_name, "..") == 0) {
            continue; // Skip current directory and parent directory entries
        }
        printf("%s\n", read_directory->d_name);
    }
    closedir(directory);
}

/*

Shit is fucked

void lp() {
    DIR *proc_directory = opendir("/proc");
    if (proc_directory == NULL) {
        fprintf("Error: Cannot open directory '/proc'. %s.\n", strerror(errno));
        return;
    }

    struct dirent *proc_entry;
    while ((proc_entry = readdir(proc_directory)) != NULL) {
        if (isdigit(proc_entry->d_name[0])) {
            char cmdline_path[PATH_MAX];
            snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", proc_entry->d_name);

            FILE *cmdline_file = fopen(cmdline_path, "r");
            if (cmdline_file) {
                char command[PATH_MAX];
                if (fgets(command, sizeof(command), cmdline_file)) {
                    printf("%s %s\n", proc_entry->d_name, command);
                }
                fclose(cmdline_file);
            }
        }
    }
    closedir(proc_directory);
}

*/


int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        print_error("Error: Cannot register signal handler. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    int running = 1;
    struct passwd *pw = getpwuid(getuid());
    char *home_dir = pw->pw_dir;

    while (running) {
        if (interrupted) {
            interrupted = 0;
            continue;
        }

        char user_input[PATH_MAX];
        char *cwd;
        cwd = get_current_dir_name();

        printf("%s[%s]%s> ", BLUE, cwd, DEFAULT);
        free(cwd);

        if (!fgets(user_input, PATH_MAX, stdin)) {
            if (feof(stdin)) {
                break; // End of file reached, exit the shell
            } else {
                print_error("Error: Failed to read from stdin. %s.\n", strerror(errno));
                break;
            }
        }

        char *token = strtok(user_input, " \n");
        char *argv[PATH_MAX];
        int i = 0;
        while (token != NULL && i < PATH_MAX - 1) {
            argv[i++] = token;
            token = strtok(NULL, " \n");
        }
        argv[i] = NULL; // Null-terminate the argument list

        if (i == 0) {
            continue; // Empty input, continue to next iteration
        }

        char *user_command = argv[0];
        if (strcmp(user_command, "cd") == 0) {
            char *user_dir = argv[1];
            if (user_dir == NULL || strcmp(user_dir, "~") == 0) {
                chdir(home_dir);
            } else if (chdir(user_dir) == -1) {
                printf("Error: Cannot change directory to '%s'. %s.\n", user_dir, strerror(errno));
            }
        } else if (strcmp(user_command, "exit") == 0) {
            running = 0;
        } else if (strcmp(user_command, "pwd") == 0) {
            cwd = get_current_dir_name();
            printf("%s\n", cwd);
            free(cwd);
        } else if (strcmp(user_command, "lf") == 0) {
            cwd = get_current_dir_name();
            lf(cwd);
            free(cwd);
        } else if (strcmp(user_command, "lp") == 0) {
            lp();
        } else {
            pid_t pid = fork();
            if (pid == -1) {
                print_error("Error: fork() failed. %s.\n", strerror(errno));
            } 
            else if (pid == 0) { // Child process
                printf("%s\n")
                execvp(user_command, argv);
                print_error("Error: exec() failed. %s.\n", strerror(errno));
                exit(EXIT_FAILURE);
            } 
            else { // Parent process
                wait(NULL);
            }
        }
    }

    return EXIT_SUCCESS;
}
