#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipefd[2]; // Array to hold pipe file descriptors: [0] for read, [1] for write
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close the read end of the pipe
        printf("Parent: Writing message to pipe...\n");
        write(pipefd[1], write_msg, strlen(write_msg) + 1); // Write message to pipe
        close(pipefd[1]); // Close the write end of the pipe after writing
    } else { // Child process
        close(pipefd[1]); // Close the write end of the pipe
        read(pipefd[0], read_msg, sizeof(read_msg)); // Read message from pipe
        printf("Child: Received message from pipe: '%s'\n", read_msg);
        close(pipefd[0]); // Close the read end of the pipe after reading
    }

    return 0;
}