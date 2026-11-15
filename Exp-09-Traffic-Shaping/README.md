# Experiment 9: Traffic Shaping Algorithms

## Objective
To simulate and analyze network traffic shaping and congestion control algorithms in C:
1. **Part A — Leaky Bucket Algorithm** ([`exp9_279.c`](./exp9_279.c))
2. **Part B — Token Bucket Algorithm** ([`exp9_2_279.c`](./exp9_2_279.c))

---

## Theory

Traffic shaping regulates the average rate and burstiness of packets admitted into a computer network to prevent buffer overflow and congestion.

### Comparison: Leaky Bucket vs. Token Bucket

| Parameter | Leaky Bucket | Token Bucket |
| :--- | :--- | :--- |
| **Output Rate** | Constant / Fixed rate strictly enforced | Allows bursty output up to bucket capacity |
| **Storage Unit** | Packets stored in queue | Tokens generated and stored |
| **Packet Loss** | Packets dropped if bucket overflows | Packets dropped/delayed if tokens are insufficient |
| **Burst Handling** | Smooths out bursts completely | Accommodates short traffic bursts |

---

## Part A: Leaky Bucket Algorithm

### Description
The bucket has a finite capacity (`bucket_size`). Incoming packets enter the bucket. If incoming packets exceed remaining capacity, the overflow packets are dropped. Regardless of the arrival rate, packets leak out at a constant `outgoing` rate. After the arrival sequence completes, remaining stored packets continue to drain until the bucket is empty.

### Compilation & Execution
```bash
gcc exp9_279.c -o exp9_279
./exp9_279
```

### Sample Input
```text
10
3
3
4
3
1
```
*(Bucket size = 10, Outgoing rate = 3, Time units = 3, Incoming packets = 4, 3, 1)*

### Sample Output
```text
Leaky Bucket Algorithm Simulation
Enter bucket size (capacity): 10
Enter outgoing rate: 3
Enter number of packets (time units): 3

Time unit 1:
Enter number of incoming packets: 4
Packets sent: 3
Packets remaining in bucket: 1

Time unit 2:
Enter number of incoming packets: 3
Packets sent: 3
Packets remaining in bucket: 1

Time unit 3:
Enter number of incoming packets: 1
Packets sent: 2
Packets remaining in bucket: 0

Simulation complete.
```

---

## Part B: Token Bucket Algorithm

### Description
Tokens are added to the bucket at a constant `rate` per time unit up to `bucket_size`. When packets arrive, each packet consumes one token. If sufficient tokens exist, all packets are transmitted immediately (allowing bursts). If tokens are insufficient, only packets with matching tokens are transmitted, and excess packets are dropped or delayed.

### Compilation & Execution
```bash
gcc exp9_2_279.c -o exp9_2_279
./exp9_2_279
```

### Sample Input
```text
10
4
3
3
3
9
```
*(Bucket size = 10, Token generation rate = 4, Time units = 3, Incoming packets = 3, 3, 9)*

### Sample Output
```text
Token Bucket Algorithm Simulation
Enter bucket size (capacity): 10
Enter token generation rate: 4
Enter number of packets (time units): 3

Time unit 1:
Enter number of packets to send: 3
Packets sent: 3
Tokens left: 1

Time unit 2:
Enter number of packets to send: 3
Packets sent: 3
Tokens left: 2

Time unit 3:
Enter number of packets to send: 9
Only 6 tokens available, packets sent: 6, packets dropped: 3
Tokens left: 0

Simulation complete.
```
