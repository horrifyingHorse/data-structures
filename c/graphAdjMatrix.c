#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// using adjacency matrix
#define VERTICE 7

struct queue {
  int q[VERTICE];
  int front, rear;
};

struct stack {
  int s[VERTICE];
  int top;
};

struct queue* initQueue() {
  struct queue* newQueue = (struct queue*)malloc(sizeof(struct queue));
  newQueue->front = -1;
  newQueue->rear = -1;

  return newQueue;
}

struct stack* initStack() {
  struct stack* newStack = (struct stack*)malloc(sizeof(struct stack));
  newStack->top = -1;

  return newStack;
}

struct queue* enQueue(struct queue* q, int n) {
  if (!q || q->rear >= VERTICE) return q;
  q->q[(++q->rear) % VERTICE] = n;
  if (q->rear == 0) q->front = 0;

  return q;
}

int deQueue(struct queue* q) {
  if (!q || q->front == -1 || q->front > q->rear) return INT_MAX;

  return q->q[(q->front++) % VERTICE];
}

bool queueIsEmpty(struct queue* q) {
  return (!q || (q->front == -1 && q->rear == -1) || q->front > q->rear);
}

struct stack* push(struct stack* s, int n) {
  if (!s || s->top == VERTICE - 1) return s;

  s->s[++s->top] = n;
  return s;
}

int pop(struct stack* s) {
  if (!s || s->top == -1) return INT_MAX;

  return s->s[s->top--];
}

bool stackIsEmpty(struct stack* s) { return (s->top == -1); }

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
    for (int j = 0; j < VERTICE; j++) graph[i][j] = false;

  return graph;
}

bool** graphDelete(bool** graph) {
  if (!graph) return graph;

  for (int i = 0; i < VERTICE; i++) free(graph[i]);

  free(graph);
  return NULL;
}

void bfs(bool** graph, int src) {
  bool visited[VERTICE] = {false};
  for (int i = 0; i < VERTICE; i++) visited[i] = false;

  struct queue* q = initQueue();

  enQueue(q, src);
  visited[src] = true;
  while (!queueIsEmpty(q)) {
    int n = deQueue(q);
    printf("%d ", n);
    for (int i = 0; i < VERTICE; i++)
      if (graph[n][i] && !visited[i]) {
        visited[i] = true;
        enQueue(q, i);
      }
  }
}

void dfs(bool** graph, int src) {
  bool visited[VERTICE] = {false};
  struct stack* s = initStack();

  visited[src] = true;
  push(s, src);
  while (!stackIsEmpty(s)) {
    int n = pop(s);
    printf("%d ", n);
    for (int i = 0; i < VERTICE; i++)
      if (graph[n][i] && !visited[i]) {
        visited[i] = true;
        push(s, i);
      }
  }
}

int main() {
  bool** graph = graphCreate();

  graphAddEdge(graph, 0, 1);
  graphAddEdge(graph, 0, 3);
  graphAddEdge(graph, 1, 2);
  graphAddEdge(graph, 1, 3);
  graphAddEdge(graph, 1, 5);
  graphAddEdge(graph, 1, 6);
  graphAddEdge(graph, 2, 3);
  graphAddEdge(graph, 2, 4);
  graphAddEdge(graph, 2, 5);
  graphAddEdge(graph, 3, 4);
  graphAddEdge(graph, 4, 6);

  printf("BFS Traversal: ");
  bfs(graph, 0);

  printf("\nDFS Traversal: ");
  dfs(graph, 0);

  graph = graphDelete(graph);

  return 0;
}
