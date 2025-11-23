#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to check if a number is prime
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    // Validate command-line argument
    if (argc != 2) {
        printf("Usage: %s <number of primes>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    // Create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: generate prime numbers
        printf("\n[Child] PID: %d — Generating first %d prime numbers:\n", getpid(), n);
        int count = 0, num = 2;
        while (count < n) {
            if (is_prime(num)) {
                printf("%d ", num);
                count++;
            }
            num++;
        }
        printf("\n[Child] Prime number generation complete.\n");
        _exit(0); // Exit child process
    }
    else {
        // Parent process waits for child to finish
        wait(NULL);
        printf("[Parent] Child process completed. Parent PID: %d\n", getpid());
    }

    return 0;
}
