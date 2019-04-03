#include <stdio.h>
#include "parse.h"
#include <stdbool.h>

int main(int argc, char ** argv) {

    while(true){
        char line_buffer[10000];
        printf("? ");
        fgets(line_buffer, 10000, stdin);
        parse(line_buffer);
    }
}