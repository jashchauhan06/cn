# Experiment 4: UDP Socket Programming — Server

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
