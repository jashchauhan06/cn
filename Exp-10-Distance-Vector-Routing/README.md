# Experiment 10: Distance Vector Routing Algorithm

## Objective
To simulate the **Distance Vector Routing (DVR)** algorithm using the **Bellman-Ford equation** in C, establishing the shortest path and next-hop forwarding table for each node in a network topology.

---

## Theory

Distance Vector Routing is a dynamic routing algorithm in which each router maintains a vector (table) of minimum distances to every destination node in the network and the next hop to reach it. Routers iteratively exchange routing tables with directly connected neighbors until convergence is reached.

### Bellman-Ford Equation
$$D_x(y) = \min_v \{ c(x,v) + D_v(y) \}$$

Where:
- $D_x(y)$ is the estimated minimum cost from node $x$ to node $y$.
- $c(x,v)$ is the link cost from node $x$ to immediate neighbor $v$.
- $D_v(y)$ is the reported distance from neighbor $v$ to destination $y$.
- The minimum is taken over all neighbors $v$ of node $x$.

---

## Data Structure

```c
#define MAX_NODES 10
#define INF 999

struct Node {
    int dist[MAX_NODES]; // Distance to each node
    int from[MAX_NODES]; // Next hop router
} rt[MAX_NODES];
```

---

## Compilation & Execution

```bash
# Navigate to directory
cd Exp-10-Distance-Vector-Routing

# Compile
gcc exp10_279.c -o exp10_279

# Run
./exp10_279
```

---

## Sample Input

```text
3
0 2 7
2 0 1
7 1 0
```
*(3 nodes. Cost matrix: Node 0 connected to 1 with weight 2, to 2 with weight 7. Node 1 connected to 2 with weight 1)*

### Network Graph
```
 (0) ─────── 2 ─────── (1)
  │                     │
  └────────── 7 ────────┘
              │
             (2)
  (Path 0 -> 1 -> 2 has cost 2 + 1 = 3, which is shorter than direct link 7)
```

---

## Expected Routing Tables

```text
Routing table for Node 0:
Destination    Next Hop    Distance
0              -1          0
1               1          2
2               1          3

Routing table for Node 1:
Destination    Next Hop    Distance
0               0          2
1              -1          0
2               2          1

Routing table for Node 2:
Destination    Next Hop    Distance
0               1          3
1               1          1
2              -1          0
```
