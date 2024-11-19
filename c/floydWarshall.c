#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERTICE 5

int** initGraph() {
  int** g = (int**)malloc(sizeof(int*) * VERTICE);

  for (int i = 0; i < VERTICE; i++) {
    g[i] = (int*)malloc(sizeof(int) * VERTICE);
    for (int j = 0; j < VERTICE; j++) {
      g[i][j] = 0;
    }
  }

  return g;
}

void graphAddEdge(int** g, int n, int m, int w) { g[n][m] = w; }

void displayGraph(int** g) {
  for (int i = 0; i < VERTICE; i++) {
    for (int j = 0; j < VERTICE; j++) {
      printf("%d ", g[i][j]);
    }
    printf("\n");
  }
}

// int min(int a, int b) { return a * (a < b) + b * (b < a); }
int min(int a, int b) {
  if (a < b) return a;
  return b;
}

void floydWarshall(int** g) {
  int dist[VERTICE][VERTICE];

  // init dist
  for (int i = 0; i < VERTICE; i++)
    for (int j = 0; j < VERTICE; j++)
      if (i == j)
        dist[i][j] = 0;
      else if (g[i][j] != 0)
        dist[i][j] = g[i][j];
      else
        dist[i][j] = 9999;  // DO NOT INT_MAX THIS SHIT RIGHT HERE (HINT:
                            // OVERFUCKINGFLOW)

  for (int k = 0; k < VERTICE; k++)
    for (int i = 0; i < VERTICE; i++)
      for (int j = 0; j < VERTICE; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  for (int i = 0; i < VERTICE; i++) {
    for (int j = 0; j < VERTICE; j++) printf("%d ", dist[i][j]);
    printf("\n");
  }
}

int main() {
  int** g = initGraph();

  graphAddEdge(g, 0, 1, 4);
  graphAddEdge(g, 0, 3, 5);
  graphAddEdge(g, 1, 2, 1);
  graphAddEdge(g, 1, 4, 6);
  graphAddEdge(g, 2, 0, 2);
  graphAddEdge(g, 2, 3, 3);
  graphAddEdge(g, 3, 4, 2);
  graphAddEdge(g, 3, 2, 1);
  graphAddEdge(g, 4, 0, 1);
  graphAddEdge(g, 4, 3, 4);

  displayGraph(g);
  printf("\nFloyd Warshall shortest Path:\n");
  floydWarshall(g);

  return 0;
}
