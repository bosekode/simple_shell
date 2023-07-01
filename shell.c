#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

void display_prompt() {
    printf("$ ");
    fflush(stdout);
}

void execute_command(char* command) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (execlp(command, command, NULL) < 0) {
            printf("Command '%s' not found.\n", command);
            exit(1);
        }
    } else {
        // Parent process
        wait(NULL);
    }
}

int main() {
    char command[BUFFER_SIZE];

    while (1) {
        display_prompt();

        if (fgets(command, BUFFER_SIZE, stdin) == NULL) {
            // End of file (Ctrl+D) or error reading input
            break;
        }

        // Remove the newline character from the end of the command
        command[strcspn(command, "\n")] = '\0';

        execute_command(command);
    }

    return 0;
}

