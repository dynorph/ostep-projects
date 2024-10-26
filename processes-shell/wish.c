#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printError() {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

void executeCommand(char *linha) {
    char *token;
    char **cmd;
    int arg_count = 0;
    while((token = strsep(&linha," ")) != NULL) {
        cmd = (char **)malloc((arg_count+1)*sizeof(char *));
        cmd[arg_count] = (char *)malloc(sizeof(char *));
        cmd[arg_count] = token;
        arg_count++;
    }
    if(strcmp(cmd[0],"cd") == 0) {
        if(arg_count != 2) {
            printError();
        }
    }
    else {
        if(chdir(cmd[1]) != 0) {
            printError();
        }
    }
}    

int main(int argc, char *argv[]) {
    FILE *arquivo;
    char *linha = NULL;
    int tam = 0;
    size_t tam_linha;
    if(argc > 2) {
        printError();
        exit(1);
    }
    arquivo = fopen(argv[1], "r");
    while(1) {
        if(arquivo == NULL) {
            printf("wish> ");
            tam = getline(&linha,&tam_linha,stdin);
            if(tam == -1) {
                printError();
                continue;
            }
            linha[strcspn(linha,"\n")] = '\0';
            if(strcmp(linha,"exit") == 0) {
                exit(0);
            }
            executeCommand(linha);
        }
        else {
            tam = getline(&linha,&tam_linha,arquivo);
            if(tam == -1) {
                printError();
                continue;
            }
            linha[strcspn(linha,"\n")] = '\0';
            if(strcmp(linha,"exit") == 0) {
                exit(0);
            }
            executeCommand(linha);
        }
    }
    return 0;
}
