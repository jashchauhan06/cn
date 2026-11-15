# Experiment 2: TCP Socket Programming — Server

## C Code (`tcp_server.c`)

```c
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
```

---

## Objective
To implement a connection-oriented **TCP Server** in C using Berkeley sockets that:
1. Creates a stream socket and binds it to port `8080`.
2. Listens for incoming connections and accepts a client connection.
3. Receives student information (`name`, `prn`, `marks` of 5 subjects) structured as `struct Student`.
4. Computes the total marks and calculates the aggregate percentage.
5. Transmits the calculated percentage back to the client.

---

## Theory

**Transmission Control Protocol (TCP)** is a connection-oriented, reliable, stream-based transport layer protocol. It guarantees in-order and error-checked delivery of a stream of octets between applications running on hosts communicating via an IP network.

### Socket Lifecycle (TCP Server)
```
       socket()
          │
          ▼
        bind()
          │
          ▼
       listen()
          │
          ▼
       accept()  ◄── (Blocks until client connects)
          │
     recv() / send()
          │
          ▼
        close()
```

1. **`socket(AF_INET, SOCK_STREAM, 0)`**: Creates an IPv4 TCP stream socket endpoint.
2. **`bind(...)`**: Associates the socket with a local IP address (`INADDR_ANY`) and port (`8080`).
3. **`listen(server_fd, backlog)`**: Marks the socket as passive to accept incoming connection requests.
4. **`accept(...)`**: Extracts the first connection request on the queue of pending connections, creating a new connected socket descriptor (`client_fd`).
5. **`recv(...)` & `send(...)`**: Exchanges data with the connected client.
6. **`close(...)`**: Closes the client and server sockets to release system resources.

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
   cd Exp-02-TCP-Server
   ```

2. Compile the server program:
   ```bash
   gcc tcp_server.c -o tcp_server
   ```

3. Run the TCP Server:
   ```bash
   ./tcp_server
   ```

> [!IMPORTANT]
> The server must be started **before** the TCP client ([Exp-03-TCP-Client](../Exp-03-TCP-Client/tcp_client.c)).

---

## Sample Output

```text
TCP Server started...
Waiting for client...

Student Details Received:
Name : Alice Johnson
PRN : 1032210012
Subject 1 Marks : 85.50
Subject 2 Marks : 90.00
Subject 3 Marks : 78.50
Subject 4 Marks : 88.00
Subject 5 Marks : 92.00
Percentage calculated: 86.80%
```

---

## Related
- **Client Implementation:** [Exp-03-TCP-Client](../Exp-03-TCP-Client/)
