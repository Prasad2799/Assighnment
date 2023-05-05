#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of workstations and connections
#define MAX_N 105
#define MAX_M 105

// Define the Union-Find data structure for checking connectivity
typedef struct {
    int parent[MAX_N];
    int rank[MAX_N];
} UnionFind;

// Initialize the Union-Find data structure
void init(UnionFind *uf, int i, int n) {
    for (i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

// Find the parent of a node in the Union-Find data structure (with path compression)
int find(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

// Merge two components in the Union-Find data structure (with rank-based union)
void merge(UnionFind *uf, int x, int y) {
    int px = find(uf, x);
    int py = find(uf, y);
    if (px != py) {
        if (uf->rank[px] < uf->rank[py]) {
            uf->parent[px] = py;
        } else if (uf->rank[px] > uf->rank[py]) {
            uf->parent[py] = px;
        } else {
            uf->parent[py] = px;
            uf->rank[px]++;
        }
    }
}

// Check if all workstations are connected in the network
int is_connected(UnionFind *uf, int i, int n) {
    int root = find(uf, 0);
    for (i = 1; i < n; i++) {
        if (find(uf, i) != root) {
            return 0;
        }
    }
    return 1;
}

// Main function to make all workstations connected
int make_connected(int n, int connections[MAX_M][2],int i, int m) {
    // Initialize the Union-Find data structure
    UnionFind uf;
    init(&uf,i, n);

    // Connect all directly connected workstations
    for (i = 0; i < m; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        merge(&uf, u, v);
    }

    // Compute the number of cables that need to be added
    int num_cables = 0;
    for (i = 1; i < n; i++) {
        if (find(&uf, i) != find(&uf, 0)) {
            merge(&uf, i, 0);
            num_cables++;
        }
    }

    // Check if all workstations are connected
    if (is_connected(&uf, n,m)) {
        return num_cables;
    } else {
        return -1;
    }
}

// Example usage
int main() {
	int i;
    int n = 4;
    int connections[MAX_M][2] = {{0,1},{0,2},{1,2}};
    int m = 3;
    int result = make_connected(n, connections,i, m);
    printf("%d\n", result);
    return 0;
}
