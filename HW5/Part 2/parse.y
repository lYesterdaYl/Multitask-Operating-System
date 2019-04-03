%{
    #include "parse.h"
    struct commandLine cmdLine;
    extern FILE * yyin;
    extern int yylineno;
    void yyerror(char *ps, ...){
        printf("Error: %s\n", ps);
    }
%}

%union{char *string;}

%start line
%token <string> EXIT
%token <string> END_OF_FILE
%token <string> PIPE
%token <string> INPUT_REDIRECTION
%token <string> OUTPUT_REDIRECTION
%token <string> APPEND
%token <string> ENABLE_BACKGROUND
%token <string> INPUT

%%
line:
        | EXIT
        {
            //set eof to 1 while the line contains exit character.
            cmdLine.eof = 1;
        }
        | END_OF_FILE
        {
            //set eof to 1 while the line reaches the end of the file.
            cmdLine.eof = 1;
            return 0;
        }
        | command_function background
        ;

command_remain: command redirection_parse
       ;

command_function: command_function PIPE command_remain{}
        | command_remain{}
        ;

background:  ENABLE_BACKGROUND{
        cmdLine.background = 1;
        }
        |{}
        ;

command: command INPUT{
        //assign input as argument if go behind command，and increment arguments count.
        cmdLine.argv[cmdLine.numCommands - 1][cmdLine.numArguments[cmdLine.numCommands - 1]] = $2;
        cmdLine.numArguments[cmdLine.numCommands - 1]++;
       }
       | INPUT{
        //increment the command number, and assign input as command
        //and increment argument count.
        cmdLine.numCommands++;
        cmdLine.argv[cmdLine.numCommands - 1][cmdLine.numArguments[cmdLine.numCommands - 1]] = $1;
        cmdLine.numArguments[cmdLine.numCommands - 1]++;
       }
       ;

redirection_parse: input_redirection output_redirection append
       ;

input_redirection:INPUT_REDIRECTION INPUT{
       cmdLine.input_redirect = 1;
       cmdLine.infile = $2;
       }
       |{}
       ;

output_redirection:OUTPUT_REDIRECTION INPUT{
       cmdLine.output_redirect = cmdLine.append + 1;
       cmdLine.outfile = $2;

       }
       |{}
       ;

append:APPEND INPUT{
       cmdLine.append = cmdLine.output_redirect + 1;
       cmdLine.appendfile = $2;
       }
       |{}
       ;
%%
void Parse(){
    //initialize cmd values.
    cmdLine.infile = NULL;
    cmdLine.outfile = NULL;

    cmdLine.input_redirect = 0;
    cmdLine.output_redirect = 0;
    cmdLine.append = 0;

    cmdLine.numCommands = 0;
    cmdLine.background = 0;

    //reset all the auguments
    for(int i = 0; i < MAX_ARGS; i++){
        cmdLine.numArguments[i] = 0;
    }

    //use yacc function to parse the line.
    yyparse();

}

int main(int argc, char *argv[]){
    //when arg is 2, open the file to read the input.
    if(argc == 2){
        yyin = fopen(argv[1],"r");

    }
    //take standard input like normal shell
    else{
        yyin = stdin;
        printf("? ");
    }
    //continue parsing each line until eof sets to 1(true).
    while(!cmdLine.eof){
        Parse();

        if(!strcmp(cmdLine.argv[0][0], "cd")){
            //if the line starts with "cd", call function cd()
            cd();
        }
        else if(cmdLine.argv[0][0][0] == '#'){
            //ignore comment line.
        }
        else{
            Execution_Preparation();
        }


        if(argc < 2 && !cmdLine.eof){
            printf("? ");

        }
    }
    return 0;
}

