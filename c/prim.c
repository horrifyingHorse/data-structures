#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 5

int minKey(int key[], bool mstSet[]) {
  int min = INT_MAX, in;
  for (int i = 0; i < V; i++)
    if (key[i] < min && !mstSet[i])
      in = i, min = key[i];

  return in;
}

void prim(int g[][V]) {
  int parent[V], key[V];
  bool mstSet[V];

  for (int i = 0; i < V; i++)
    mstSet[i] = false, key[i] = INT_MAX;
  key[0] = 0;
  parent[0] = -1;

  for (int i = 0; i < V - 1; i++) {
    int n = minKey(key, mstSet);
    mstSet[n] = true;

    for (int m = 0; m < V; m++)
      if (!mstSet[m] && g[n][m] &&
          g[n][m] < key[m])
        parent[m] = n, key[m] = g[n][m];
  }

  printf("Edge \tWeight\n");
  for (int i = 1; i < V; i++)
    printf("%d - %d \t%d \n", parent[i], i,
           g[i][parent[i]]);
}

int main() {
  int graph[V][V] = {{0, 2, 0, 6, 0},
                     {2, 0, 3, 8, 5},
                     {0, 3, 0, 0, 7},
                     {6, 8, 0, 0, 9},
                     {0, 5, 7, 9, 0}};

  prim(graph);

  return 0;
}
