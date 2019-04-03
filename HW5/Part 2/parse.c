#include "parse.h"

struct commandLine cmdLine;

void exec_command(int inputFd, int outputFd, char *args[], int background){
    int pid;
    int status;

    switch (pid = fork()){
        case -1:
            perror("Fail to fork a new process");

        case 0:
            if(inputFd != fileno(stdin)){
                dup2(inputFd, fileno(stdin));
                close(inputFd);
            }
            if(outputFd, fileno(stdout)){
                dup2(outputFd, fileno(stdout));
                close(outputFd);
            }
            execvp(args[0], args);

            printf("Fail to execute the command");
            exit(-1);
        default:
            if(background != 1){
                pid = wait(&status);
            }

    }
}

void Execution_Preparation(){

    int pfd[2], i;

    int saveInput = dup(fileno(stdin));
    int saveOutput = dup(fileno(stdout));
    int saveError = dup(fileno(stderr));

    int inputFd = dup(fileno(stdin));
    int outputFd = dup(fileno(stdout));
    int errorFd = dup(fileno(stderr));

    //do the input redirection if input_redirection is true.
    //open the input file, print error if fail to open the file
    if(cmdLine.input_redirect){
        dup2(open(cmdLine.infile, O_RDONLY), inputFd);

        if(inputFd == NULL){
            perror("No such file or directoy\n");
            exit(1);
        }
    }

    //the loop will iterate will the command in the list, and execute them
    //one by one.
    for(i = 0; i < cmdLine.numCommands - 1; i++){
        //create pipe
        if(pipe(pfd) == -1){
            perror("Fail to create pipe");
        }
        //add NULL pointer at the end of the list before execution. And call the exec_command.
        cmdLine.argv[i][cmdLine.numArguments[i]] = NULL;
        exec_command(inputFd, pfd[1], cmdLine.argv[i], cmdLine.background);

        close(pfd[1]);

        dup2(pfd[0], inputFd);
        close(pfd[0]);
    }

    if(cmdLine.output_redirect){
        dup2(open(cmdLine.outfile, O_WRONLY | O_CREAT | O_TRUNC), outputFd);

        if(outputFd == NULL){
            perror("No such file or directoy\n");
            exit(1);
        }
    }


    if(cmdLine.append){
        dup2(open(cmdLine.appendfile, O_WRONLY | O_CREAT | O_APPEND), outputFd);

        if(outputFd == NULL){
            perror("No such file or directoy\n");
            exit(1);
        }
    }
    //add NULL pointer at the end of the list before execution. And call the exec_command.
    cmdLine.argv[i][cmdLine.numArguments[i]] = NULL;
    exec_command(inputFd, outputFd, cmdLine.argv[i], cmdLine.background);

    close(inputFd);
    close(outputFd);
    close(errorFd);

    dup2(saveInput, fileno(stdin));
    dup2(saveOutput, fileno(stdout));
    dup2(saveError, fileno(stderr));

    close(saveInput);
    close(saveOutput);
    close(saveError);
}

