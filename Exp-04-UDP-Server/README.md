# Experiment 4: UDP Socket Programming — Server

## C Code (`udp_server.c`)

```c
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
```

---

## Objective
To implement a connectionless **UDP Server** in C using Berkeley sockets that:
1. Creates a datagram socket (`SOCK_DGRAM`) and binds it to port `8081`.
2. Listens for incoming datagrams without establishing a dedicated connection.
3. Receives student information (`name`, `prn`, `marks` of 5 subjects) from a client using `recvfrom()`.
4. Computes total marks and percentage.
5. Returns the calculated percentage back to the client's socket address using `sendto()`.

---

## Theory

**User Datagram Protocol (UDP)** is a connectionless, lightweight, and message-oriented transport layer protocol. Unlike TCP, UDP does not perform a connection handshake, maintain connection state, or guarantee packet delivery or order.

### Socket Lifecycle (UDP Server)
```
       socket(SOCK_DGRAM)
             │
             ▼
           bind()
             │
             ▼
        recvfrom()  ◄── (Waits for incoming datagram from any client)
             │
         sendto()   ──► (Sends datagram back to client address)
             │
             ▼
          close()
```

### Key Differences from TCP
- No `listen()` or `accept()` calls are required because UDP is connectionless.
- Uses `recvfrom()` and `sendto()`, passing client address structures directly for each transmission.

---

## Data Structure

```c
struct Student {
    char name[50];
    char prn[30];
    float marks[5];
};
```

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-04-UDP-Server
   ```

2. Compile the server program:
   ```bash
   gcc udp_server.c -o udp_server
   ```

3. Run the UDP Server:
   ```bash
   ./udp_server
   ```

> [!NOTE]
> Start the server before running the UDP client ([Exp-05-UDP-Client](../Exp-05-UDP-Client/udp_client.c)).

---

## Sample Output

```text
UDP Server started...
Waiting for client data...

Student Details Received:
Name : Bob Smith
PRN : 1032210045
Subject 1 Marks : 76.00
Subject 2 Marks : 82.50
Subject 3 Marks : 91.00
Subject 4 Marks : 84.00
Subject 5 Marks : 79.50
Percentage calculated: 82.60%
```

---

## Related
- **Client Implementation:** [Exp-05-UDP-Client](../Exp-05-UDP-Client/)
