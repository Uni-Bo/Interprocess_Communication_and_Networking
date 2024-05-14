#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/mysocket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[1024];
    int parity_count;

    // Create server socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Bind the server socket to the address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    // Accept client connection
    socklen_t client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    // Receive bit-stream from the client
    if (recv(client_fd, buffer, sizeof(buffer), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    // Calculate parity bit
    parity_count = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '1') {
            parity_count++;
        }
    }

    // Add parity bit (even parity)
    if (parity_count % 2 == 0) {
        strcat(buffer, "0"); // Add '0' as parity bit
    } else {
        strcat(buffer, "1"); // Add '1' as parity bit
    }

    // Send modified bit-stream back to the client
    if (send(client_fd, buffer, sizeof(buffer), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    printf("Modified bit-stream sent to client\n");

    // Close sockets
    close(client_fd);
    close(server_fd);

    // Remove socket file
    unlink(SOCKET_PATH);

    return 0;
}

