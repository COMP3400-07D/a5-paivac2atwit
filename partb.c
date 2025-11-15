#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char* input_file = argv[1];
    char* output_file = argv[2]

    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        printf("ERROR: Could not open output file %s: %s\n", output_file, sterror(errno));
        return 2;
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        printf("ERROR: Could not redirect STDOUT: %s\n", strerror(errno));
        close(fd);
        return 3;
    }

    close(fd);

    printf("Category,Count\n");
    fflush(stdout);

    char* parta_args[] = {"./parta", input_file, NULL};
    
    int eret = execv("./parta", parta_args);
    
    printf("ERROR: execv failed: %s\n", strerror(errno));
    return 4;
}
