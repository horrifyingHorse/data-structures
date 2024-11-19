#include <stdio.h>

#define E 14

void bubbleSort(int edge[][3]) {
  for (int i = 0; i < E; i++)
    for (int j = 0; j < E - i - 1; j++)
      if (edge[j][2] > edge[j + 1][2]) {
        int temp[3];
        temp[0] = edge[j][0];
        temp[1] = edge[j][1];
        temp[2] = edge[j][2];

        edge[j][0] = edge[j + 1][0];
        edge[j][1] = edge[j + 1][1];
        edge[j][2] = edge[j + 1][2];

        edge[j + 1][0] = temp[0];
        edge[j + 1][1] = temp[1];
        edge[j + 1][2] = temp[2];
      }
}

void makeSet(int parent[], int rank[]) {
  for (int i = 0; i < E; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
}

int findParent(int parent[], int component) {
  if (parent[component] == component) return component;

  return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int n, int m, int parent[], int rank[]) {
  n = findParent(parent, n);
  m = findParent(parent, m);

  if (rank[n] < rank[m])
    parent[n] = m;
  else if (rank[n] > rank[m])
    parent[m] = n;
  else {
    parent[m] = n;
    rank[n]++;
  }
}

void kruskal(int edge[][3]) {
  bubbleSort(edge);

  int parent[E];
  int rank[E];
  makeSet(parent, rank);

  printf("Edges in MST:\n");
  int minCost = 0;
  for (int i = 0; i < E; i++) {
    int v1 = findParent(parent, edge[i][0]);
    int v2 = findParent(parent, edge[i][1]);
    int wt = edge[i][2];

    if (v1 == v2) continue;

    unionSet(v1, v2, parent, rank);
    minCost += wt;
    printf("(%d)---%2d---(%d)\n", edge[i][0], wt, edge[i][1]);
  }

  printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main() {
  int edge[E][3] = {{0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7},
                    {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10},
                    {5, 6, 2}, {6, 8, 6}, {6, 7, 1}, {7, 8, 7}};

  kruskal(edge);

  return 0;
}
