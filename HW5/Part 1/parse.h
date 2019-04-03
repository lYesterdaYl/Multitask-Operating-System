

#ifndef CS146_HW5_PARSE_H
#define CS146_HW5_PARSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(char* s);

typedef struct command{

    int command_number;
    char** argument;

}COMMAND;


#endif //CS146_HW5_PARSE_H
