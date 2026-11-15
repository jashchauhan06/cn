#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

struct Student {
    char name[50];
    char prn[30];
    float marks[5];
};

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    struct Student student;
    float total, percentage;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    // Listen
    listen(server_fd, 5);

    printf("TCP Server started...\n");
    printf("Waiting for client...\n");

    // Accept client
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &addr_len);

    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(1);
    }

    // Receive student data
    recv(client_fd, &student, sizeof(student), 0);

    printf("\nStudent Details Received:\n");
    printf("Name : %s\n", student.name);
    printf("PRN : %s\n", student.prn);

    total = 0;

    for (int i = 0; i < 5; i++) {
        printf("Subject %d Marks : %.2f\n",
               i + 1, student.marks[i]);
        total += student.marks[i];
    }

    // Each subject is out of 100
    percentage = total / 5.0;

    printf("Percentage calculated: %.2f%%\n", percentage);

    // Send percentage to client
    send(client_fd, &percentage, sizeof(percentage), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
