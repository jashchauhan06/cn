# Experiment 5: UDP Socket Programming — Client

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
