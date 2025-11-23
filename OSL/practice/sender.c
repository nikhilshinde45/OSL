#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg message;
    while (1) {
        printf("Enter message (or 'exit'): ");
        fgets(message.text, 100, stdin);
        message.text[strcspn(message.text, "\n")] = 0;
        if (strcmp(message.text, "exit") == 0) break;
        message.type = 1;
        msgsnd(msgid, &message, sizeof(message.text), 0);
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}