#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

struct Student {
    char name[50];
    char prn[30];
    float marks[5];
};

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    struct Student student;
    float total, percentage;

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sock, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sock);
        exit(1);
    }

    printf("UDP Server started...\n");
    printf("Waiting for client data...\n");

    // Receive student data
    recvfrom(sock, &student, sizeof(student), 0,
             (struct sockaddr *)&client_addr, &addr_len);

    printf("\nStudent Details Received:\n");
    printf("Name : %s\n", student.name);
    printf("PRN : %s\n", student.prn);

    total = 0;

    for (int i = 0; i < 5; i++) {
        printf("Subject %d Marks : %.2f\n",
               i + 1, student.marks[i]);
        total += student.marks[i];
    }

    // Calculate percentage
    percentage = total / 5.0;

    printf("Percentage calculated: %.2f%%\n", percentage);

    // Send result back to client
    sendto(sock, &percentage, sizeof(percentage), 0,
           (struct sockaddr *)&client_addr, addr_len);

    close(sock);

    return 0;
}
