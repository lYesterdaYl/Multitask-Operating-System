#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <memory.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <getopt.h>

typedef struct file_info{
    char permission[100];
    int hardlink;
    char* groups;
    char* pwd;
    int file_size;
    char* files_time;
    char* file_name;
}File_info;

//function uses to compare the size. This can be used in the qsort function.
int compare(const void* i, const void* j){
    const File_info* file1 = i;
    const File_info* file2 = j;

    return file2->file_size - file1->file_size;
}

void lss(File_info* information, int number, int a_option, int A_option){
    for(int i = 0; i < number; i++)
    {
        //if A option was specified, only print the files name is not "." or ".."
        if(A_option) {
            if (strcmp(information[i].file_name, ".") != 0 && strcmp(information[i].file_name, "..") != 0) {

            printf("%s\t", information[i].permission);
            printf("%d\t", information[i].hardlink);
            printf("%s\t", information[i].groups);
            printf("%s\t", information[i].pwd);
            printf("%d\t", information[i].file_size);
            printf("%s\t", information[i].files_time);
            printf("%s\t", information[i].file_name);
            printf("\n");
            }
        }
        //neither with or without a option, the program should print all files.
        else{
            printf("%s\t", information[i].permission);
            printf("%d\t", information[i].hardlink);
            printf("%s\t", information[i].groups);
            printf("%s\t", information[i].pwd);
            printf("%d\t", information[i].file_size);
            printf("%s\t", information[i].files_time);
            printf("%s\t", information[i].file_name);
            printf("\n");
        }

    }
}


int main(int argc, char *args[]) {
    int a_option = 0;
    int A_option = 0;
    int L_option = 0;

    //use get opts to get the option from the users. Any invalid options will print error and exit.
    int opt;
    while ((opt = getopt (argc, args, "aAL")) != -1)
    {
        switch (opt) {
            case 'a':
                a_option = 1;
                break;
            case 'A':
                A_option = 1;
                break;
            case 'L':
                L_option = 1;
                break;
            case '?':
                //exit with invalid options.
                printf("Error: Invalid option");
                exit(0);
        }
    }

    //get current directory
    char* current_dir = getenv("PWD");
    if(current_dir == NULL){
        printf("Error: no such directory\n");
    }
    else {
        struct stat path_stat;
        DIR *dp;
        struct dirent *dptr;

        File_info information[100];
        struct group *grp;
        struct passwd *pwd;
        struct dirent *d;
        struct tm lt;

        dp = opendir(current_dir);
        if (dp == NULL) {
            printf("Error: no such directory\n");
        } else {
            int index = 0;
            while ((dptr = readdir(dp)) != NULL) {
                if (L_option == 1) {
                    stat(dptr->d_name, &path_stat);
                } else {
                    lstat(dptr->d_name, &path_stat);
                }
                grp = getgrgid(path_stat.st_gid);
                pwd = getpwuid(path_stat.st_uid);

                //pass the permission bits to pointer temp storage.
                char temp[100];
                char *pTemp = temp;
                strcpy(pTemp, (S_ISDIR(path_stat.st_mode) ? "d" : "-"));
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IRUSR) ? "r" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IWUSR) ? "w" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IXUSR) ? "x" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IRGRP) ? "r" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IWGRP) ? "w" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IXGRP) ? "x" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IROTH) ? "r" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IWOTH) ? "w" : "-");
                pTemp++;
                strcpy(pTemp, (path_stat.st_mode & S_IXOTH) ? "x" : "-");
                pTemp++;
                strcpy(information[index].permission, temp);


                information[index].hardlink = path_stat.st_nlink;

                information[index].pwd = pwd->pw_name;

                information[index].groups = grp->gr_name;

                information[index].file_size = path_stat.st_size;

                //gain raw time info
                char *raw = ctime(&path_stat.st_mtime);
                char time[13];

                //get the time we need for lss, and set index 12 as \0
                memcpy(time, (raw + 4), 12);
                time[12] = '\0';
                information[index].files_time = time;

                information[index].file_name = dptr->d_name;

                index++;

            }

            int size = index;
            //use quick sort by size on information.
            qsort(information, size, sizeof(File_info), compare);
            lss(information, size, a_option, A_option);

        }
    }




    return 0;
}