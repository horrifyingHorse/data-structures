#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// using Adjacency List
#define VERTICE 7

struct node {
  int vertex;
  struct node* link;
};

struct queue {
  int q[VERTICE];
  int front, rear;
};

struct stack {
  int s[VERTICE];
  int top;
};

struct node* initNode(int vertex) {
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->vertex = vertex;
  newNode->link = NULL;

  return newNode;
}

struct queue* initQueue() {
  struct queue* q = (struct queue*)malloc(sizeof(struct queue));
  q->rear = -1;
  q->front = -1;

  return q;
}

struct stack* initStack() {
  struct stack* s = (struct stack*)malloc(sizeof(struct stack));
  s->top = -1;

  return s;
}

struct queue* enQueue(struct queue* q, int n) {
  if (!q) return q;
  q->q[++q->rear % VERTICE] = n;
  if (q->rear == 0) q->front = 0;

  return q;
}

int deQueue(struct queue* q) {
  if (!q || q->front > q->rear || q->front == -1) return INT_MAX;

  return q->q[q->front++];
}

bool queueIsEmpty(struct queue* q) {
  return ((q->front == -1 && q->rear == -1) || q->front > q->rear);
}

struct stack* push(struct stack* s, int n) {
  if (!s || s->top >= VERTICE - 1) return s;
  s->s[++s->top] = n;

  return s;
}

int pop(struct stack* s) {
  if (!s || s->top == -1) return INT_MAX;
  return s->s[s->top--];
}

bool stackIsEmpty(struct stack* s) { return (!s || s->top == -1); }

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
  /* newNode->link = graph[n]->link;
   * graph[n]->link = newNode;
   *
   * newNode = initNode(n);
   * newNode->link = graph[m]->link;
   * graph[m]->link = newNode;
   */

  /* Keeping an order [ ] */
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
  /**/

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

void bfs(struct node** graph, int src) {
  bool visited[VERTICE] = {false};
  struct queue* q = initQueue();

  visited[src] = true;
  enQueue(q, src);
  while (!queueIsEmpty(q)) {
    int n = deQueue(q);
    printf("%d ", n);

    struct node* temp = graph[n]->link;
    while (temp) {
      if (!visited[temp->vertex]) {
        visited[temp->vertex] = true;
        enQueue(q, temp->vertex);
      }
      temp = temp->link;
    }
  }
}

void dfs(struct node** graph, int src) {
  bool visited[VERTICE] = {false};
  struct stack* s = initStack();

  visited[src] = true;
  push(s, src);
  while(!stackIsEmpty(s)) {
    int n = pop(s);
    printf("%d ", n);
    struct node* temp = graph[n]->link;
    while (temp) {
      if(!visited[temp->vertex]) {
        visited[temp->vertex] = true;
        push(s, temp->vertex);
      }
      temp = temp->link;
    }
  }
}

int main() {
  struct node** graph = graphCreate();

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
