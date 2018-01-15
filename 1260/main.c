#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINK 20000

typedef int ElementType;

typedef struct Graph {
    int size;
    int start;
    bool **link;
    bool *check_visit;
} Graph;

typedef struct LinkedList {
    ElementType Element;
    void *Next;
} LinkedList;
typedef LinkedList* Stack;

typedef struct Queue {
    int Capacity;
    int Size;
    int front;
    int rear;
    ElementType *key;
} Queue;

Stack MakeStack(void);
bool StackIsEmpty(Stack s);
void Push(Stack s, ElementType X);
ElementType Pop(Stack s);

Queue* MakeQueue(void);
bool QueueIsEmpty(Queue *q);
void Enqueue(Queue *q, ElementType X);
ElementType Dequeue(Queue *q);

Graph MakeGraph(void);
void DFS(Graph g);
void BFS(Graph g);

int main(void) {
    Graph g = MakeGraph();
    DFS(g);
    BFS(g);
    return 0;
}

Stack MakeStack(void) {
    Stack tmpStack = (Stack)malloc(sizeof(LinkedList));
    tmpStack->Next = NULL;
    return tmpStack;
}
bool StackIsEmpty(Stack s) {
    return s->Next == NULL;
}
void Push(Stack s, ElementType X) {
    LinkedList *tmpCell = (LinkedList*)malloc(sizeof(LinkedList));
    tmpCell->Element = X;
    tmpCell->Next = s->Next;
    s->Next = tmpCell;
}
ElementType Pop(Stack s) {
    LinkedList *tmpCell = s->Next;
    ElementType tmp = tmpCell->Element;
    s->Next = tmpCell->Next;
    free(tmpCell);
    return tmp;
}

Queue* MakeQueue(void) {
    Queue* tmpQueue = (Queue*)malloc(sizeof(Queue));
    tmpQueue->Capacity = MAX_LINK;
    tmpQueue->Size = 0;
    tmpQueue->front = 0;
    tmpQueue->rear = -1;
    tmpQueue->key = (int*)malloc(sizeof(int)*MAX_LINK);
    return tmpQueue;
}
bool QueueIsEmpty(Queue *q) {
    return q->Size == 0;
}
void Enqueue(Queue *q, ElementType X) {
    q->rear = (q->rear + 1) % q->Capacity;
    q->key[q->rear] = X;
    q->Size++;
}
ElementType Dequeue(Queue *q) {
    ElementType tmp = q->key[q->front];
    q->front = (q->front + 1) % q->Capacity;
    q->Size--;
    return tmp;
}

Graph MakeGraph(void) {
    int N, M, V;
    Graph g;
    scanf("%d %d %d", &N, &M, &V);
    g.size = N;
    g.link = (bool**)malloc(sizeof(bool*)*(N+1));
    for(int i = 1; i <= N; i++) {
        g.link[i] = (bool*)malloc(sizeof(bool)*(N+1));
        memset(g.link[i], false, sizeof(bool)*(N+1));
    }
    g.check_visit = (bool*)malloc(sizeof(bool)*(N+1));
    for(int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g.link[u][v] = true;
        g.link[v][u] = true;
    }
    g.start = V;
    return g;
}
void DFS(Graph g) {
    memset(g.check_visit, false, sizeof(bool)*(g.size+1));
    Stack s = MakeStack();
    Push(s, g.start);
    while(!StackIsEmpty(s)) {
        int u = Pop(s);
        if(g.check_visit[u]) continue;
        printf("%d ", u);
        g.check_visit[u] = true;
        for(int v = g.size; v > 0; v--) {
            if(g.link[u][v] && !g.check_visit[v])
                Push(s, v);
        }
    }
    putchar('\n');
}
void BFS(Graph g) {
    memset(g.check_visit, false, sizeof(bool)*(g.size+1));
    Queue *q = MakeQueue();
    Enqueue(q, g.start);
    while(!QueueIsEmpty(q)) {
        int u = Dequeue(q);
        if(g.check_visit[u]) continue;
        printf("%d ", u);
        g.check_visit[u] = true;
        for(int v = 1; v <= g.size; v++) {
            if(g.link[u][v] && !g.check_visit[v])
                Enqueue(q, v);
        }
    }
    putchar('\n');
}
