#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// using adjacency matrix
#define VERTICE 5

bool** graphCreate() {
  // graph[VERTICE][VERTICE]
  bool** graph = (bool**)malloc(sizeof(bool*) * VERTICE);
  for (int i = 0; i < VERTICE; i++) {
    graph[i] = (bool*)malloc(sizeof(bool) * VERTICE);
    for (int j = 0; j < VERTICE; j++) {
      graph[i][j] = false;
    }
  }

  return graph;
}

bool** graphAddEdge(bool** graph, int n, int m) {
  if (!graph) return graph;
  if (n >= VERTICE || m >= VERTICE) {
    printf("Edge out of bounds @(%d, %d)", n, m);
    exit(1);
  }

  graph[n][m] = true;
  graph[m][n] = true;

  return graph;
}

bool** graphRemEdge(bool** graph, int n, int m) {
  if (!graph) return graph;
  if (n >= VERTICE || m >= VERTICE) {
    printf("Edge out of bounds @(%d, %d)", n, m);
    exit(1);
  }

  graph[n][m] = false;
  graph[m][n] = false;

  return graph;
}

void graphDisplay(bool** graph) {
  if (!graph) return;

  for (int i = 0; i < VERTICE; i++)
    for (int j = 0; j < VERTICE; j++)
      if (graph[i][j]) printf("%d %d\n", i, j);
}

bool** graphClear(bool** graph) {
  if (!graph) return graph;

  for (int i = 0; i < VERTICE; i++)
    for (int j = 0; j  < VERTICE; j++)
      graph[i][j] = false;

  return graph;
}

bool** graphDelete(bool** graph) {
  if (!graph) return graph;

  for (int i = 0; i < VERTICE; i++)
    free(graph[i]);

  free(graph);
  return NULL;
}

int main() {
  bool** graph = graphCreate();

  graphAddEdge(graph, 0, 1);
  graphAddEdge(graph, 0, 2);
  graphAddEdge(graph, 1, 2);
  graphAddEdge(graph, 2, 3);

  graphDisplay(graph);

  graphRemEdge(graph, 0, 1);
  graphRemEdge(graph, 0, 2);
  graphRemEdge(graph, 1, 2);
  graphRemEdge(graph, 2, 3);

  // graph = graphClear(graph);

  graphDisplay(graph);

  graph = graphDelete(graph);

  return 0;
}
