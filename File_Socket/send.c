#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "/tmp/mysocket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[1024];

    // Create client socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Get bit-stream from the user
    printf("Enter bit-stream: ");
    scanf("%s", buffer);

    // Send bit-stream to the server
    if (send(client_fd, buffer, sizeof(buffer), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // Receive modified bit-stream from the server
    if (recv(client_fd, buffer, sizeof(buffer), 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    printf("Modified bit-stream received from server: %s\n", buffer);

    // Close socket
    close(client_fd);

    return 0;
}

