/*******************************************************************************
 * Name        : sl.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

// All good 11:30

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Not correct number of arguments");
        return EXIT_FAILURE;
    }
    char *directory = argv[1];
    int pipe_ls_sort[2], parent_pipe_sort[2];

    DIR *user_dir = opendir(directory);

    struct stat dir_stat;

    if (stat(directory, &dir_stat) == -1){
        fprintf(stderr, "Permission denied. %s cannot be read.", directory);
        closedir(user_dir);
        return EXIT_FAILURE;
    }
    if (!S_ISDIR(dir_stat.st_mode)){
        fprintf(stderr, "The first argument has to be a directory.");
        closedir(user_dir);
        return EXIT_FAILURE;
    }
    if (!user_dir) {
        fprintf(stderr, "Permission denied. %s cannot be read.", directory);
        closedir(user_dir);
        return EXIT_FAILURE;
    }

    /*
    This is the og code but the order is wrong so the right code chunk is above

    struct stat dir_stat;
    */

    // if (S_ISDIR(dir_stat.st_mode)) {
    //     fprintf(stderr, "The first argument has to be a directory.");
    //     return EXIT_FAILURE;
    // }

    // if (stat(directory, &dir_stat) == -1) {
    //      fprintf(stderr, "Permission denied. %s cannot be read.", directory);
    //     return EXIT_FAILURE;
    // }
    
    // if (!(dir_stat.st_mode & S_IRUSR)) {
    //     fprintf(stderr, "Permission denied. %s cannot be read.", directory);
    //     return EXIT_FAILURE;
    // }
    
    
    
    int child_pipe = pipe(pipe_ls_sort);
    int parent_pipe = pipe(parent_pipe_sort);   

    // Don't need this but used for debuging, had weird issue where the pipes failed and output was not printing
    if (child_pipe == -1 || parent_pipe == -1) {
        fprintf(stderr, "Failed to create pipes.\n");
        closedir(user_dir);
        return EXIT_FAILURE;
    }

    pid_t ls_pid, sort_pid;

    
    ls_pid = fork();

    if (ls_pid == -1) {
        fprintf(stderr, "Failed to fork for ls.\n");
        closedir(user_dir);
        return EXIT_FAILURE;
    } else if (ls_pid == 0) {  
        close(pipe_ls_sort[0]);  
        dup2(pipe_ls_sort[1], STDOUT_FILENO); 
        //close(pipe_ls_sort[1]); // Dup2 does the closing for you 

        execlp("ls", "ls", "-ai", directory, NULL);  
        fprintf(stderr, "ls execution failed for directory '%s'.\n", directory);
        closedir(user_dir);
        return EXIT_FAILURE;
    }

    sort_pid = fork();
    
    if (sort_pid == 0) {  
        close(pipe_ls_sort[1]);  
        dup2(pipe_ls_sort[0], STDIN_FILENO);  
        //close(pipe_ls_sort[0]); // Dup2 does the closing for you 

        close(parent_pipe_sort[0]);  
        dup2(parent_pipe_sort[1], STDOUT_FILENO);  
        //close(parent_pipe_sort[1]); // Dup 2 does the closing for you
        
        char* argv[] = {"sort", NULL};
        execvp("sort", argv);  // Execute sort command
        //fprintf(stderr, "Sort execution failed.\n");
        closedir(user_dir);
        return EXIT_FAILURE;
    }

    close(pipe_ls_sort[0]); 
    close(pipe_ls_sort[1]);  

    close(parent_pipe_sort[1]);  

    char buffer[1024];
    ssize_t read_count;
    int file_count = 0;
    while ((read_count = read(parent_pipe_sort[0], buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, read_count);  // Print sorted files that are returned from the exec call
        for (int i = 0; i < read_count; i++) {
            if (buffer[i] == '\n') {
                file_count++;
            }
        }
    }

    printf("Total files: %d\n", file_count);  
    close(parent_pipe_sort[0]);  
    closedir(user_dir);

    //int status;
    // waitpid(ls_pid, &status, 0);
    // waitpid(sort_pid, &status, 0);

    return EXIT_SUCCESS;
}
