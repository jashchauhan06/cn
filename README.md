# Computer Networks Laboratory

Comprehensive implementation, packet captures, and simulation assignments for the Computer Networks (CN) Laboratory curriculum.

---

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Experiments Index](#experiments-index)
  - [Socket Programming (Exp 2 – 5)](#socket-programming-exp-2--5)
  - [Packet Analysis & Protocols (Exp 6 – 7)](#packet-analysis--protocols-exp-6--7)
  - [Data Link Layer Protocols (Exp 8)](#data-link-layer-protocols-exp-8)
  - [Traffic Shaping & Congestion Control (Exp 9)](#traffic-shaping--congestion-control-exp-9)
  - [Routing Algorithms (Exp 10)](#routing-algorithms-exp-10)
- [Architecture & Sequence Diagrams](#architecture--sequence-diagrams)
  - [TCP Echo Client-Server Flow (Exp 2 & 3)](#tcp-echo-client-server-flow-exp-2--3)
  - [UDP Client-Server Flow (Exp 4 & 5)](#udp-client-server-flow-exp-4--5)
  - [DNS & HTTP Request Flow (Exp 6 & 7)](#dns--http-request-flow-exp-6--7)
- [Compilation & Execution Guide](#compilation--execution-guide)
- [Summary Table](#summary-table)

---

## Overview

This repository contains lab assignments covering transport protocols, socket programming, application-layer packet inspection, flow control, traffic shaping, and dynamic network routing.

- **TCP Echo Socket Programming (Exp 2 & 3):** C client-server implementation of a full-duplex TCP Echo service on port `10242` (`10000 + PRN`).
- **UDP Socket Programming (Exp 4 & 5):** Connectionless UDP client-server message exchange on port `8080`.
- **Packet Inspection (Exp 6 & 7):** Wireshark capture and protocol analysis for DNS (`A`, `PTR`, `MX` lookups) and HTTP request/response flows.
- **Flow & Congestion Control (Exp 8 & 9):** Simulation of Go-Back-N Sliding Window ARQ, Leaky Bucket, and Token Bucket algorithms.
- **Routing (Exp 10):** Distance Vector Routing based on iterative Bellman-Ford shortest-path relaxations.

---

## Repository Structure

```text
CN/
├── README.md
├── Exp-02-TCP-Server/
│   ├── README.md
│   └── server1242.c
├── Exp-03-TCP-Client/
│   ├── README.md
│   └── client1242.c
├── Exp-04-UDP-Server/
│   ├── README.md
│   └── server_udp242.c
├── Exp-05-UDP-Client/
│   ├── README.md
│   └── client_udp_242.c
├── Exp-06-DNS-Packet-Analysis/
│   └── README.md
├── Exp-07-DNS-HTTP-Packet-Analysis/
│   └── README.md
├── Exp-08-Sliding-Window-Protocol/
│   ├── README.md
│   └── sliding_window242.c
├── Exp-09-Traffic-Shaping/
│   ├── README.md
│   ├── exp9_242.c          # Leaky Bucket
│   └── exp9_2_242.c        # Token Bucket
└── Exp-10-Distance-Vector-Routing/
    ├── README.md
    └── exp10_242.c
```

---

## Experiments Index

### Socket Programming (Exp 2 – 5)

| Experiment | Title | Protocol | Port | Source |
| :---: | :--- | :---: | :---: | :--- |
| **Exp 2** | [TCP Echo Server](./Exp-02-TCP-Server/) | TCP (`SOCK_STREAM`) | `10242` | [`server1242.c`](./Exp-02-TCP-Server/server1242.c) |
| **Exp 3** | [TCP Echo Client](./Exp-03-TCP-Client/) | TCP (`SOCK_STREAM`) | `10242` | [`client1242.c`](./Exp-03-TCP-Client/client1242.c) |
| **Exp 4** | [UDP Server](./Exp-04-UDP-Server/) | UDP (`SOCK_DGRAM`) | `8080` | [`server_udp242.c`](./Exp-04-UDP-Server/server_udp242.c) |
| **Exp 5** | [UDP Client](./Exp-05-UDP-Client/) | UDP (`SOCK_DGRAM`) | `8080` | [`client_udp_242.c`](./Exp-05-UDP-Client/client_udp_242.c) |

### Packet Analysis & Protocols (Exp 6 – 7)

| Experiment | Title | Tools | Filter | Guide |
| :---: | :--- | :---: | :---: | :--- |
| **Exp 6** | [DNS Packet Analysis](./Exp-06-DNS-Packet-Analysis/) | `nslookup`, Wireshark | `dns` | [Lab Manual](./Exp-06-DNS-Packet-Analysis/README.md) |
| **Exp 7** | [DNS & HTTP Packet Analysis](./Exp-07-DNS-HTTP-Packet-Analysis/) | Browser/curl, Wireshark | `dns \|\| http` | [Lab Manual](./Exp-07-DNS-HTTP-Packet-Analysis/README.md) |

### Flow, Traffic Shaping & Routing (Exp 8 – 10)

| Experiment | Title | Description | Source |
| :---: | :--- | :--- | :--- |
| **Exp 8** | [Sliding Window Protocol](./Exp-08-Sliding-Window-Protocol/) | Go-Back-N ARQ simulation with interactive acknowledgment & retransmission. | [`sliding_window242.c`](./Exp-08-Sliding-Window-Protocol/sliding_window242.c) |
| **Exp 9** | [Traffic Shaping Algorithms](./Exp-09-Traffic-Shaping/) | Leaky Bucket (constant leak rate) & Token Bucket (bursty transmission). | [`exp9_242.c`](./Exp-09-Traffic-Shaping/exp9_242.c), [`exp9_2_242.c`](./Exp-09-Traffic-Shaping/exp9_2_242.c) |
| **Exp 10** | [Distance Vector Routing](./Exp-10-Distance-Vector-Routing/) | Dynamic routing table calculation using Bellman-Ford algorithm. | [`exp10_242.c`](./Exp-10-Distance-Vector-Routing/exp10_242.c) |

---

## Architecture & Sequence Diagrams

### TCP Echo Client-Server Flow (Exp 2 & 3)

```mermaid
sequenceDiagram
    autonumber
    actor Client as TCP Echo Client (Exp 3)
    actor Server as TCP Echo Server (Exp 2)

    Note over Server: socket() -> bind(10242) -> listen()
    Note over Client: socket()
    Client->>Server: connect() [SYN, SYN-ACK, ACK]
    Note over Server: accept() connection established

    loop Interactive Message Exchange
        Client->>Server: send(buffer) "Hello Server"
        Note over Server: read(buffer) & print to stdout
        Server->>Client: send(buffer) [Echo back]
        Note over Client: read(buffer) & display echo
    end

    Client->>Server: close(sock)
    Note over Server: close(new_socket) & close(server_fd)
```

---

### UDP Client-Server Flow (Exp 4 & 5)

```mermaid
sequenceDiagram
    autonumber
    actor Client as UDP Client (Exp 5)
    actor Server as UDP Server (Exp 4)

    Note over Server: socket() -> bind(8080)
    Note over Client: socket()
    
    Client->>Server: sendto(message, server_addr)
    Note over Server: recvfrom(buffer, client_addr)<br/>Print "Message from Client"
    Server->>Client: sendto("Hello from UDP Server", client_addr)
    Note over Client: recvfrom(buffer)<br/>Print "Server Response"

    Client->>Client: close(sockfd)
    Server->>Server: close(server_socket)
```

---

### DNS & HTTP Request Flow (Exp 6 & 7)

```mermaid
sequenceDiagram
    autonumber
    actor Client as Web Client
    actor DNS as DNS Resolver (UDP 53)
    actor Web as Web Server (TCP 80)

    Client->>DNS: DNS Query (A record for example.com)
    DNS-->>Client: DNS Answer (93.184.216.34)

    Client->>Web: TCP SYN
    Web-->>Client: TCP SYN-ACK
    Client->>Web: TCP ACK

    Client->>Web: HTTP GET /
    Web-->>Client: HTTP/1.1 200 OK (HTML Payload)

    Client->>Web: TCP FIN-ACK
    Web-->>Client: TCP FIN-ACK
```

---

## Compilation & Execution Guide

### 1. TCP Echo Socket Programming (Exp 2 & 3)
```bash
# Terminal 1: Run TCP Echo Server
cd Exp-02-TCP-Server
gcc server1242.c -o server
./server

# Terminal 2: Run TCP Echo Client
cd Exp-03-TCP-Client
gcc client1242.c -o client
./client
```

### 2. UDP Socket Programming (Exp 4 & 5)
```bash
# Terminal 1: Run UDP Server
cd Exp-04-UDP-Server
gcc server_udp242.c -o server
./server

# Terminal 2: Run UDP Client
cd Exp-05-UDP-Client
gcc client_udp_242.c -o client
./client
```

### 3. Wireshark Packet Analysis (Exp 6 & 7)
- **Exp 6 (DNS):**
  ```cmd
  nslookup www.example.com
  nslookup 93.184.216.34
  nslookup -query=MX example.com
  ```
  *Filter in Wireshark:* `dns`

- **Exp 7 (DNS & HTTP):**
  ```cmd
  nslookup www.google.com
  curl -I http://example.com
  ```
  *Filter in Wireshark:* `dns || http`

### 4. Sliding Window Protocol (Exp 8)
```bash
cd Exp-08-Sliding-Window-Protocol
gcc sliding_window242.c -o sliding_window242
./sliding_window242
```

### 5. Traffic Shaping Algorithms (Exp 9)
```bash
cd Exp-09-Traffic-Shaping

# Leaky Bucket
gcc exp9_242.c -o exp9_242
./exp9_242

# Token Bucket
gcc exp9_2_242.c -o exp9_2_242
./exp9_2_242
```

### 6. Distance Vector Routing (Exp 10)
```bash
cd Exp-10-Distance-Vector-Routing
gcc exp10_242.c -o exp10_242
./exp10_242
```

---

## Summary Table

| Exp | Topic | Protocol / Alg | Type | Output / Goal |
| :---: | :--- | :--- | :--- | :--- |
| **02** | TCP Echo Server | TCP | C / Sockets | Listens on port `10242`, receives and echoes incoming client messages |
| **03** | TCP Echo Client | TCP | C / Sockets | Connects to port `10242`, sends user text, displays echoed response |
| **04** | UDP Server | UDP | C / Sockets | Listens on port `8080`, prints client message, replies with `"Hello from UDP Server"` |
| **05** | UDP Client | UDP | C / Sockets | Sends message to port `8080`, displays server reply |
| **06** | DNS Packet Inspection | DNS | Packet Capture | Forward lookup (`A`), reverse lookup (`PTR`), mail exchange (`MX`) |
| **07** | DNS & HTTP Inspection | DNS, HTTP | Packet Capture | DNS query resolution followed by HTTP GET request/response cycle |
| **08** | Flow Control | Go-Back-N ARQ | C Simulation | Simulates pipelining, cumulative ACK, and window reset on loss |
| **09** | Congestion Control | Leaky & Token Bucket | C Simulation | Constant rate shaping vs. burst-tolerant token depletion |
| **10** | Routing Algorithms | Distance Vector (Bellman-Ford) | C Simulation | Shortest-path routing tables with convergence tracking |
