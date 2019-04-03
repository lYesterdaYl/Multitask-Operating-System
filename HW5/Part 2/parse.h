
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MAX_LINE 10240  /* longest accepted command line */
#define MAX_COMMANDS 32 /* Max # of commands (eg, "who | wc" is 2 commands) */
#define MAX_ARGS 32     /* maximum number of arguments per commad */


struct commandLine
{
    char buf[MAX_LINE];

    int eof; //boolean end of file or not.
    int numCommands; // number of commands
    char *argv[MAX_ARGS][1000]; // arguments of the command.
    int numArguments[MAX_ARGS]; //number of arguments
    int input_redirect, output_redirect; //boolean for input or output redirection.
    char *infile, *outfile, *appendfile; //input, output, append redirect file name.
    int append;	/* Boolean: 1 means ">>", 0 means ">"

    /*
    ** Here would be a good place to add stuff like a boolean signifying
    ** background execution, for example.
    */

    int background; //boolean program will run in background or not.
};

/*
** Function prototype for the scanner/parser
*/
void Parse();
void cd();
void Execution_Preparation();
void exec_command(int inputFd, int outputFd, char *args[], int run_bg);
extern void perror(const char *);
