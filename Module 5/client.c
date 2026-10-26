#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_SIZE 2048

int main() {
    int client;
    struct sockaddr_in address;
    char filename[256];
    char buffer[MAX_SIZE + 1];

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        perror("Socket failed");
        return 1;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // Connect to the server on the same computer
    if (inet_pton(AF_INET, "127.0.0.1",
                  &address.sin_addr) <= 0) {
        printf("Invalid server address.\n");
        close(client);
        return 1;
    }

    if (connect(client, (struct sockaddr *)&address,
                sizeof(address)) < 0) {
        perror("Connection failed");
        close(client);
        return 1;
    }

    printf("Connected to server!\n");
    printf("Enter the filename: ");

    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Could not read filename.\n");
        close(client);
        return 1;
    }

    // Remove the newline from user input
    filename[strcspn(filename, "\n")] = '\0';

    // Send the filename with a newline
    strcat(filename, "\n");

    size_t length = strlen(filename);
    size_t sent = 0;

    while (sent < length) {
        ssize_t n = send(client, filename + sent,
                         length - sent, 0);

        if (n <= 0) {
            printf("Could not send request.\n");
            close(client);
            return 1;
        }

        sent += (size_t)n;
    }

    printf("\nServer response:\n");

    // Receive and print the response
    ssize_t bytes;

    while ((bytes = recv(client, buffer, MAX_SIZE, 0)) > 0) {
        fwrite(buffer, 1, (size_t)bytes, stdout);
    }

    if (bytes < 0) {
        perror("Receive failed");
    }

    printf("\n");

    close(client);
    return bytes < 0 ? 1 : 0;
}
