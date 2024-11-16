#include <stdio.h>
#include <stdlib.h>

// using Adjacency List
#define VERTICE 5

struct node {
  int vertex;
  struct node* link;
};

struct node* initNode(int vertex) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->vertex = vertex;
  newNode->link = NULL;

  return newNode;
}

struct node** graphCreate() {
  struct node** graph = (struct node**)malloc(sizeof(struct node*) * VERTICE);

  for (int i = 0; i < VERTICE; i++) {
    graph[i] = initNode(i);
  }

  return graph;
}

struct node** graphAddEdge(struct node** graph, int n, int m) {
  if (!graph) return graph;
  if (n >= VERTICE || m >= VERTICE) {
    printf("Edge out of bounds @(%d, %d)", n, m);
    exit(1);
  }

  struct node* newNode = initNode(m);

  // O(1) Time
  newNode->link = graph[n]->link;
  graph[n]->link = newNode;

  newNode = initNode(n);
  newNode->link = graph[m]->link;
  graph[m]->link = newNode;

  /* Keeping an order [ ]
  struct node* temp = graph[n];
  while (temp != NULL && temp->link != NULL && temp->link->vertex < m) {
    temp = temp->link;
  }
  if (temp->link == NULL || temp->link->vertex != m) {
    newNode->link = temp->link;
    temp->link = newNode;
  }

  newNode = initNode(n);
  temp = graph[m];
  while (temp != NULL && temp->link != NULL && temp->link->vertex < n) {
    temp = temp->link;
  }
  if (temp->link == NULL || temp->link->vertex != n) {
    newNode->link = temp->link;
    temp->link = newNode;
  }
  */

  return graph;
}

struct node** graphRemEdge(struct node** graph, int n, int m) {
  if (!graph) return graph;
  if (n >= VERTICE || m >= VERTICE) {
    printf("Edge out of bounds @(%d, %d)", n, m);
    exit(1);
  }

  struct node* temp = graph[n];
  struct node* prev = temp;

  while (temp != NULL && temp->vertex != m) {
    prev = temp;
    temp = temp->link;
  }
  if (!temp) {
    printf("No edge @(%d, %d)", n, m);
    exit(1);
  }
  prev->link = temp->link;
  free(temp);

  temp = graph[m];
  prev = temp;
  while (temp != NULL && temp->vertex != n) {
    prev = temp;
    temp = temp->link;
  }
  if (!temp) {
    printf("No edge @(%d, %d)", m, n);
    exit(1);
  }
  prev->link = temp->link;
  free(temp);

  return graph;
}

void graphDisplay(struct node** graph) {
  if (!graph) return;
  for (int i = 0; i < VERTICE; i++) {
    struct node* temp = graph[i]->link;
    printf("%d -> ", i);
    while (temp != NULL) {
      printf("%d, ", temp->vertex);
      temp = temp->link;
    }
    printf("\n");
  }
}

struct node** graphClear(struct node** graph) {
  if (!graph) return graph;

  for (int i = 0; i < VERTICE; i++) {
    struct node* temp = graph[i]->link;
    struct node* del = temp;

    while (temp != NULL) {
      del = temp;
      temp = temp->link;

      free(del);
      del = NULL;
    }
    if (del) free(del);

    graph[i]->link = NULL;
  }

  return graph;
}

struct node** graphDelete(struct node** graph) {
  if (!graph) return graph;

  for (int i = 0; i < VERTICE; i++) {
    struct node* temp = graph[i]->link;
    struct node* del = temp;

    while (temp != NULL) {
      del = temp;
      temp = temp->link;

      free(del);
      del = NULL;
    }
    if (del) free(del);

    free(graph[i]);
  }

  return NULL;
}

int main() {
  struct node** graph = graphCreate();

  graphAddEdge(graph, 2, 3);
  graphAddEdge(graph, 0, 1);
  graphAddEdge(graph, 0, 2);
  graphAddEdge(graph, 1, 2);

  graphDisplay(graph);

  printf("\n");

  graphRemEdge(graph, 2, 3);
  graphRemEdge(graph, 0, 1);
  graphRemEdge(graph, 0, 2);
  graphRemEdge(graph, 1, 2);

  // graph = graphClear(graph);

  graphDisplay(graph);

  graph = graphDelete(graph);

  return 0;
}
