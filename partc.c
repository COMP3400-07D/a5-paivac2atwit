#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
if (argc != 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }

    char* input_file = argv[1];

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 2;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 3;
    }

    if (pid > 0){
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        char* parta_args[] = {"./parta", input_file, NULL};
        execv("./parta", parta_args);

        perror("execv parta");
        return 4;
    }
    else {
        close(pipefd[1]);
        dup2(pipefd[0], STFIN_FILENO);
        clsoe(pipefd[0]);

        char* sort_args[] = {"sort", "-t", "-k2", "-n", NULL};
        execvp("sort", sort_args);

        perror("execvp sort");
        return 5;
    }

    wait(NULL);
    return 0;
}
