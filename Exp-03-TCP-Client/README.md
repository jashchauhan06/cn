# Experiment 3: TCP Socket Programming — Client

## C Code (`tcp_client.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

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
    clock_t start, end;
    double response_time;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Server IP address
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    printf("Connected to TCP Server.\n\n");

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

    // Send data
    send(sock, &student, sizeof(student), 0);

    // Receive percentage
    recv(sock, &percentage, sizeof(percentage), 0);

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
```

---

## Objective
To implement a connection-oriented **TCP Client** in C using Berkeley sockets that:
1. Connects to a running TCP server on `127.0.0.1:8080`.
2. Reads student details (`name`, `prn`, and marks for 5 subjects) from standard input.
3. Sends the student data encapsulated in `struct Student` to the server over TCP.
4. Measures round-trip response time (latency) in milliseconds using `clock()`.
5. Receives and displays the calculated percentage along with the response time.

---

## Theory

The TCP client initiates communication by performing a **three-way handshake** (SYN, SYN-ACK, ACK) with the listening server via the `connect()` system call. Once the connection is established, full-duplex communication takes place reliably over the socket.

### Socket Lifecycle (TCP Client)
```
       socket()
          │
          ▼
       connect()  ──► (Initiates TCP 3-way handshake)
          │
     send() / recv()
          │
          ▼
        close()
```

### Response Time Calculation
The response time represents the round-trip latency taken to transmit data to the server and receive the reply:
$$\text{Response Time (ms)} = \frac{\text{end} - \text{start}}{\text{CLOCKS\_PER\_SEC}} \times 1000$$

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)
- The TCP Server ([Exp-02-TCP-Server](../Exp-02-TCP-Server/)) must already be running.

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-03-TCP-Client
   ```

2. Compile the client program:
   ```bash
   gcc tcp_client.c -o tcp_client
   ```

3. Run the TCP Client:
   ```bash
   ./tcp_client
   ```

---

## Sample Input & Output

```text
Connected to TCP Server.

Enter student name: Alice Johnson
Enter PRN: 1032210012
Enter marks for Subject 1: 85.5
Enter marks for Subject 2: 90
Enter marks for Subject 3: 78.5
Enter marks for Subject 4: 88
Enter marks for Subject 5: 92

----- Result -----
Student Name : Alice Johnson
PRN          : 1032210012
Percentage   : 86.80%
Response Time: 0.421 ms
```

---

## Related
- **Server Implementation:** [Exp-02-TCP-Server](../Exp-02-TCP-Server/)
