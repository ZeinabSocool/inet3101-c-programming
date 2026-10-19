
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_SIZE 2048

int valid_filename(char *name) {
    if (strlen(name) == 0) {
        return 0;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum((unsigned char)name[i]) &&
            name[i] != '.' && name[i] != '_' && name[i] != '-') {
            return 0;
        }
    }

    if (strstr(name, "..") != NULL) {
        return 0;
    }

    return 1;
}

void send_message(int client, const char *message) {
    send(client, message, strlen(message), 0);
}

int main() {
    int server, client;
    struct sockaddr_in address;
    char filename[256];
    char buffer[MAX_SIZE + 1];

    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        perror("Socket failed");
        return 1;
    }

    int option = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR,
               &option, sizeof(option));

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("Bind failed");
        close(server);
        return 1;
    }

    if (listen(server, 5) < 0) {
        perror("Listen failed");
        close(server);
        return 1;
    }

    printf("Server is running on port %d...\n", PORT);

    while (1) {
        client = accept(server, NULL, NULL);

        if (client < 0) {
            perror("Connection failed");
            continue;
        }

        memset(filename, 0, sizeof(filename));

        int i = 0;
        char letter;
        int received;

        // Read the filename until the newline
        while ((received = recv(client, &letter, 1, 0)) == 1) {
            if (letter == '\n') {
                break;
            }

            if (i >= 255) {
                break;
            }

            filename[i++] = letter;
        }

        filename[i] = '\0';

        printf("Client requested: %s\n", filename);

        if (received != 1 || !valid_filename(filename)) {
            send_message(client, "ERROR: Invalid filename.\n");
            close(client);
            continue;
        }

        FILE *file = fopen(filename, "rb");

        if (file == NULL) {
            send_message(client, "ERROR: File not found.\n");
            close(client);
            continue;
        }

        // Check the file size
        if (fseek(file, 0, SEEK_END) != 0) {
            send_message(client, "ERROR: Cannot read file.\n");
            fclose(file);
            close(client);
            continue;
        }

        long size = ftell(file);

        if (size < 0 || size > MAX_SIZE) {
            send_message(client, "ERROR: File is too large.\n");
            fclose(file);
            close(client);
            continue;
        }

        rewind(file);

        size_t bytes = fread(buffer, 1, (size_t)size, file);
        fclose(file);

        if (bytes != (size_t)size) {
            send_message(client, "ERROR: Cannot read file.\n");
            close(client);
            continue;
        }

        // Make sure the file contains text
        if (memchr(buffer, '\0', bytes) != NULL) {
            send_message(client, "ERROR: Not a valid text file.\n");
            close(client);
            continue;
        }

        // Send the file contents
        size_t sent = 0;

        while (sent < bytes) {
            ssize_t n = send(client, buffer + sent,
                             bytes - sent, 0);

            if (n <= 0) {
                break;
            }

            sent += (size_t)n;
        }

        printf("File request finished.\n");
        close(client);
    }

    close(server);
    return 0;
}
