/*******************************************************************************
 * Name        : pfind.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>


int convert(char* permission_string){
    char first[3];
    char second[3];
    char third[3];
    int final_count = 0;
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    for (size_t i = 0; i < strlen(permission_string); i++){
        if (i <= 2){
            first[i] = permission_string[i];
        }
        else if (i <= 5){
            second[i-3] = permission_string[i];
        }
        else{
            third[i-6] = permission_string[i];
        }
    }
    
    for (size_t i = 0; i < 3; i++){
        if (first[i] == 'r'){
        count1 += 0400;
        }
        else if (first[i] == 'w'){
        count1 += 0200;
        }
        else if (first[i] == 'x'){
        count1 += 0100;
        }
        else{
            count1 += 0;
        }
    }
    for (size_t i = 0; i <3; i++){
        if (second[i] == 'r'){
        count2 += 040;
        }
        else if (second[i] == 'w'){
        count2 += 020;
        }
        else if (second[i] == 'x'){
        count2 += 010;
        }
        else{
            count1 += 0;
        }
    }
    for (size_t i = 0; i < 3; i++){
        if (third[i] == 'r'){
        count3 += 04;
        }
        else if (third[i] == 'w'){
        count3 += 02;
        }
        else if (third[i] == 'x'){
        count3 += 01;
        }
        else{
            count1 += 0;
        }
    }
    //printf("first: %o, second: %o, third: %o\n",count1,count2,count3);
    //final_count = count1*100 + count2*10 + count3;
    final_count = count1 + count2 + count3;
    // sprintf(final_string, "%d%d%d", count1, count2, count3);
    return final_count;
}



void pfind(char* user_directory, int permission_string){
    DIR* directory = opendir(user_directory);
    
    if (directory == NULL){
        return;
    }

    struct dirent* read_directory;
    struct stat fileinfo;

    while ((read_directory = readdir(directory)) != NULL){
        if (strcmp(read_directory->d_name, ".") == 0 || strcmp(read_directory->d_name, "..") == 0) {
            continue; // Skip current directory and parent directory entries
        }

        char full_path[PATH_MAX];

        if (user_directory[strlen(user_directory) - 1] != '/') {
            // user_directory already ends with a slash, no need to add one
            sprintf(full_path, "%s/%s", user_directory, read_directory->d_name);
        }
        else{
            sprintf(full_path, "%s%s", user_directory, read_directory->d_name);
        } 
        stat(full_path, &fileinfo);
        if (S_ISDIR(fileinfo.st_mode)){
            pfind(full_path, permission_string); // Because if the "file" that I am currently working with is a directory then I want to send it back into the fucntion to search for more files in there
        }
        else if (S_ISREG(fileinfo.st_mode)){ // Sometimes it makes it here and other times not
            //printf("file name: %s; permission_string: %d; file_string: %d\n",full_path,permission_string,(fileinfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)));
            //printf("%o %o %o\n", (fileinfo.st_mode & S_IRWXU), (fileinfo.st_mode & S_IRWXG), (fileinfo.st_mode & S_IRWXO));
            //printf("%o\n",permission_string);
            //printf("%o %o\n",(fileinfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)), permission_string); // this calculation is wrong
            if ((fileinfo.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) == permission_string){ // this case is never triggered
                //printf("%s/%s\n", user_directory, read_directory->d_name);
                printf("%s\n",full_path);
            }
        }
}
closedir(directory);
}

int main(int argc, char *argv[]){
    char* directory = argv[1];
    char* permission_string = argv[2];
    size_t directory_len = strlen(directory);
    size_t perm_str_len = strlen(permission_string);

    if (perm_str_len == 9){
        for (size_t i = 0; i < perm_str_len; i++){
            if ((i == 0 || i == 3 || i == 6) && !(permission_string[i] == 'r' || permission_string[i] == '-' )){
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permission_string);
                return EXIT_FAILURE;
            }

            else if ((i == 1 || i == 4 || i == 7) && !(permission_string[i] == 'w' || permission_string[i] == '-' )){
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permission_string);
                return EXIT_FAILURE;
            }

            else if ((i == 2 || i == 5 || i == 8) && !((permission_string[i] == 'x' || permission_string[i] == '-' ))){ 
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permission_string);
                return EXIT_FAILURE;
            }
        }
        int perm_num = convert(permission_string);
        pfind(directory, perm_num);
        return 0;
    }
    
    else {
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permission_string);
        return EXIT_FAILURE;
    }
}
