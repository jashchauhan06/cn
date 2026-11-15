# Experiment 3: TCP Socket Programming — Client

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
