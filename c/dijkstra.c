#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Weighted and Directed Adjacency List
#define VERTICE 5

typedef struct Graph {
  int vertex;
  int weight;
  struct Graph* link;
} Graph;

typedef struct PQueue {
  int arr[VERTICE][2];
  int index;
} PQueue;

Graph* initGraphNode(int vertex, int weight) {
  Graph* newGraph = (Graph*)malloc(sizeof(Graph) * VERTICE);
  newGraph->vertex = vertex;
  newGraph->weight = weight;
  newGraph->link = NULL;

  return newGraph;
}

Graph** initGraph() {
  Graph** newGraph = (Graph**)malloc(sizeof(Graph*) * VERTICE);
  for (int i = 0; i < VERTICE; i++) {
    newGraph[i] = initGraphNode(i, 0);
  }

  return newGraph;
}

PQueue* initPQueue() {
  PQueue* newPQueue = (PQueue*)malloc(sizeof(PQueue));
  newPQueue->index = -1;

  return newPQueue;
}

void swap(int (*a)[], int (*b)[]) {
  int t1, t2;
  t1 = (*a)[0];
  t2 = (*a)[1];

  (*a)[0] = (*b)[0];
  (*a)[1] = (*b)[1];

  (*b)[0] = t1;
  (*b)[1] = t2;
}

PQueue* minHeapify(PQueue* pq, int i) {
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int smallest = i;

  if (l <= pq->index && pq->arr[l][0] < pq->arr[i][0]) smallest = l;
  if (r <= pq->index && pq->arr[r][0] < pq->arr[smallest][0]) smallest = r;

  if (smallest != i) {
    swap(&pq->arr[smallest], &pq->arr[i]);
    minHeapify(pq, smallest);
  }

  return pq;
}

PQueue* enQueue(PQueue* pq, int val, int priority) {
  if (!pq || pq->index >= VERTICE) return pq;

  pq->arr[++(pq->index)][0] = priority;
  pq->arr[pq->index][1] = val;
  int i = pq->index;
  int p = (i - 1) / 2;

  while (p >= 0 && pq->arr[p][0] > pq->arr[i][0]) {
    swap(&pq->arr[p], &pq->arr[i]);
    p = (i - 1) / 2;
  }

  return pq;
}

int* deQueue(PQueue* pq) {
  if (!pq || pq->index < 0) return NULL;

  int* val = (int*)malloc(sizeof(int) * 2);
  val[0] = pq->arr[0][0];
  val[1] = pq->arr[0][1];
  pq->arr[0][0] = pq->arr[pq->index][0];
  pq->arr[0][1] = pq->arr[(pq->index--)][1];

  minHeapify(pq, 0);

  return val;
}

bool isEmpty(PQueue* pq) { return !pq || pq->index < 0; }

void displayHeap(PQueue* h) {
  if (!h || h->index < 0) return;
  for (int i = 0; i <= h->index; i++) {
    printf("(%d, %d) ", h->arr[i][0], h->arr[i][1]);
  }
}

Graph** graphAddEdge(Graph** g, int n, int m, int w) {
  if (!g) return g;
  if (n >= VERTICE || m >= VERTICE) {
    printf("Edge out of bounds @(%d, %d)", n, m);
    exit(1);
  }

  Graph* newNode = initGraphNode(m, w);
  Graph* temp = g[n];
  while (temp->link && temp->link->vertex < m) {
    temp = temp->link;
  }
  if (temp->link && temp->link->vertex == m) {
    printf("Duplicate Edge @(%d, %d)\nEdge Already Exists with weight %d", n, m,
           temp->link->weight);
    exit(1);
  }
  newNode->link = temp->link;
  temp->link = newNode;

  return g;
}

void displayGraph(Graph** g) {
  for (int i = 0; i < VERTICE; i++) {
    Graph* temp = g[i]->link;
    printf("%d -> ", i);
    while (temp) {
      printf("(%d, %d) ", temp->vertex, temp->weight);
      temp = temp->link;
    }
    printf("\n");
  }
}

void dijkstra(Graph** g, int src) {
  int dist[VERTICE];
  bool sptSet[VERTICE];
  PQueue* pq = initPQueue();

  for (int i = 0; i < VERTICE; i++) dist[i] = INT_MAX, sptSet[i] = false;

  dist[src] = 0;
  enQueue(pq, src, 0);

  while (!isEmpty(pq)) {
    int* val = deQueue(pq);
    int d = val[0];  // distance
    int v = val[1];  // vertex

    if (sptSet[v]) continue;
    sptSet[v] = true;

    Graph* temp = g[v]->link;
    int i = 0;
    while (temp) {
      if (d + temp->weight < dist[temp->vertex] && !sptSet[temp->vertex]) {
        dist[temp->vertex] = d + temp->weight;
        enQueue(pq, temp->vertex, dist[temp->vertex]);
      }
      temp = temp->link;
    }
  }

  for (int i = 0; i < VERTICE; i++) {
    printf("%d ", dist[i]);
  }
}

int main() {
  Graph** g = initGraph();

  graphAddEdge(g, 0, 1, 3);
  graphAddEdge(g, 0, 3, 1);
  graphAddEdge(g, 1, 3, 4);
  graphAddEdge(g, 1, 4, 5);
  graphAddEdge(g, 1, 2, 5);
  graphAddEdge(g, 2, 4, 9);
  graphAddEdge(g, 3, 4, 1);

  displayGraph(g);
  printf("\nDijkstra Shortest Distance from 0: ");
  dijkstra(g, 0);

  return 0;
}
