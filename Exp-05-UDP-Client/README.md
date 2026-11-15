# Experiment 5: UDP Socket Programming — Client

## C Code (`udp_client.c`)

```c
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
```

---

## Objective
To implement a connectionless **UDP Client** in C using Berkeley sockets that:
1. Creates a UDP datagram socket (`SOCK_DGRAM`).
2. Reads student credentials (`name`, `prn`, and marks for 5 subjects) from standard input.
3. Transmits student data to the UDP server on `127.0.0.1:8081` using `sendto()`.
4. Measures round-trip response time (latency) in milliseconds using `clock()`.
5. Receives the computed percentage from the server using `recvfrom()` and displays the output.

---

## Theory

UDP does not establish a persistent connection before data transfer. The client addresses the datagram directly to the destination IP and port using `sendto()`. This provides lower latency and minimal protocol overhead compared to TCP, though packet delivery and order are not guaranteed by the transport layer.

### Socket Lifecycle (UDP Client)
```
       socket(SOCK_DGRAM)
             │
             ▼
         sendto()   ──► (Sends datagram directly to server destination)
             │
        recvfrom()  ◄── (Awaits response datagram from server)
             │
             ▼
          close()
```

### Latency Measurement
$$\text{Response Time (ms)} = \frac{\text{end} - \text{start}}{\text{CLOCKS\_PER\_SEC}} \times 1000$$

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)
- The UDP Server ([Exp-04-UDP-Server](../Exp-04-UDP-Server/)) should be running.

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-05-UDP-Client
   ```

2. Compile the client program:
   ```bash
   gcc udp_client.c -o udp_client
   ```

3. Run the UDP Client:
   ```bash
   ./udp_client
   ```

---

## Sample Input & Output

```text
UDP Client started.

Enter student name: Bob Smith
Enter PRN: 1032210045
Enter marks for Subject 1: 76
Enter marks for Subject 2: 82.5
Enter marks for Subject 3: 91
Enter marks for Subject 4: 84
Enter marks for Subject 5: 79.5

----- Result -----
Student Name : Bob Smith
PRN          : 1032210045
Percentage   : 82.60%
Response Time: 0.185 ms
```

---

## Related
- **Server Implementation:** [Exp-04-UDP-Server](../Exp-04-UDP-Server/)
