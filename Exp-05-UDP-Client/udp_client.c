#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8081

struct Student {
    char name[50];
    char prn[30];
    float marks[5];
};

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct Student student;
    float percentage;
    socklen_t addr_len = sizeof(server_addr);

    clock_t start, end;
    double response_time;

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("UDP Client started.\n\n");

    // Input student details
    printf("Enter student name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter PRN: ");
    scanf("%s", student.prn);

    for (int i = 0; i < 5; i++) {
        printf("Enter marks for Subject %d: ", i + 1);
        scanf("%f", &student.marks[i]);
    }

    // Start response-time measurement
    start = clock();

    // Send data to server
    sendto(sock, &student, sizeof(student), 0,
           (struct sockaddr *)&server_addr,
           sizeof(server_addr));

    // Receive percentage
    recvfrom(sock, &percentage, sizeof(percentage), 0,
             (struct sockaddr *)&server_addr,
             &addr_len);

    // End response-time measurement
    end = clock();

    response_time =
        ((double)(end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\n----- Result -----\n");
    printf("Student Name : %s\n", student.name);
    printf("PRN          : %s\n", student.prn);
    printf("Percentage   : %.2f%%\n", percentage);
    printf("Response Time: %.3f ms\n", response_time);

    close(sock);

    return 0;
}
