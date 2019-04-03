#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct lines
{
    char s[100];
} Lines;

int main(int argc, char ** argv) {
    char options[200];
    int comma_index = -1;

    bool argument = true;
    bool option = false;
    bool env_var = false;

    //Default value
    int n = 1;
    int m = 1;


    //check if there are options
    if(argc == 1 || (argv[1][0] == '-' && argc < 3))
    {
        argument = false;
    }
    //copy the options to the options varible if found
    if(argc > 1 && argv[1][0] == '-'){
        memcpy(options, argv[1], sizeof(options));
        option = true;
    }
    //use EVERY global variable if need.
    else{
        if(getenv("EVERY")){
            memcpy(options, getenv("EVERY"), sizeof(options));
            env_var = true;
            option = true;
        }
    }

    if(option){
        if(options[0] != '-'){
            printf("Error, option does not contain symbol -");
            exit(0);
        }

        for(int i = 1; i < strlen(options); i++){
            //check if each char is a number
            if(isdigit(options[i])){

            }
            else if(options[i] == ',' && comma_index == -1 && i > 1){
                comma_index = i;
            }
            else{
                printf("Error");
                exit(0);
            }
        }

        //break the string into n and m tokens
        const char s[2] = ",";
        char storage[5];
        char* token;
        int index = 0;


        token = strtok(options, s);
        n = abs(atoi(token));
        token = strtok(NULL, s);
        m = abs(atoi(token));
        printf("n = %d, m = %d\n", n, m);

        if(m > n){
            printf("n must be larger or equal to m");
            exit(0);
        }

    }

    int start_index = 1;
    //if there are any options, we should start looking for files at
    //the next index.
    if(option && !env_var){
        start_index++;
    }
    for(int i = start_index; i < argc; i++){
        FILE *files;
        //use standard input if no options
        if(!argument){
            files = stdin;
        }
        else{
            files = fopen(argv[i], "r");
            printf("open %s\n", argv[i]);
            if(files == NULL){
                printf("Error: Invalid file");
            }
        }
        //copy all the lines from the file to the buffer.
        Lines fileBuffer[10000];
        char buffer[10000];
        int size = 0;
        while(fgets(buffer, 100, files) != NULL) {
            strcpy(fileBuffer[size].s, buffer);
            size++;
        }
        //start printing out the lines base on n and m setting.
        for(int i = 0; i < size; i+=n) {
            for(int j = i; j < (i + m); j++) {
                printf("%s", fileBuffer[j].s);
            }
        }

    fclose(files);


    }




    return 0;
}