

#include "parse.h"

void parse(char* s){
    COMMAND c;

    //initialize command value
    c.command_number = 0;
    c.argument = NULL;

    //get command number while counting number of token separated by
    // "|"
    char temp[10000];
    strcpy(temp, s);

    char* token;
    token = strtok(temp, "|");

    while( token != NULL )
    {
        token = strtok(NULL, "|");
        c.command_number++;
    }

    strcpy(temp, s);
    char * argument[10000];
    //can implement exec later.
    c.argument = argument;

    //split with space and store within argument array.
    int size = 0;
    token = strtok(temp, " ");

    while (token != NULL) {
        argument[size] = (char *) malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(argument[size], token);
        token = strtok(NULL, " ");
        size++;
    }

    //print seq on the output. For now, I just focus on correct output.
    //I will change the code to store the whole output as a varible
    //before printing the output, so I can easier handle each varible
    //for the part2.
    printf("%d:", c.command_number);
    for(int i = 0; i < size; i++){
        //remove the /n character
        if(argument[i] != NULL){
            strtok(argument[i], "\n");
        }
        //if the part does not contain "|" "<" or ">", print as normal. Other with print with ''
        if(strcmp(argument[i], "|") == 0 || strcmp(argument[i], "<") == 0 || strcmp(argument[i], ">") == 0){
            printf(" %s", argument[i]);

        }
        else{
            printf(" \'%s\'", argument[i]);

        }
    }
    printf("\n");

}