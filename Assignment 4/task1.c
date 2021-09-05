#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAPHSIZE 6

// implementation of adjacency matrix inspired by https://www.log2base2.com/data-structures/graph/adjacency-matrix-representation-of-graph.html
// implementation of DFS/BFS  inspired by https://www.programiz.com/dsa/graph-bfs

struct queue {
  int items[GRAPHSIZE];
  int front;
  int rear;
};

char int_to_ascii(int i){
    int a;
    if ((i < 26) && (i >= 0)){
        return i + 65;
    }

    else
    {
        printf("err: int is not meant to be a char");
    }
    
}
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
 
  return q;
}
bool stacked[GRAPHSIZE] = {false};
bool visited[GRAPHSIZE] = {false};
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
bool isEmpty(struct queue* q);
void printQueue(struct queue* q);
int matrix[GRAPHSIZE][GRAPHSIZE];

void enqueue(struct queue* q, int value) {
  if (q->rear == GRAPHSIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (visited[value] != true){
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
    }
  }
}

bool isEmpty(struct queue* q) {
  if (q->rear == -1)
    return true;
  else
    return false;
}

void dup_remove(struct queue* q){
  for (int i=0; i < GRAPHSIZE; i++){
    if (q->items[i+1] != NULL){
      q->items[i] = q->items[i + 1];
    }
  }
  q->rear = q->rear - 1;
}

int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } 
  else {
      item = q->items[q->front];
      while (visited[item] == true){
        dup_remove(q);
        item = q->items[q->front];
      }
    
      //q->front++;
      if (q->front > q->rear) {
        printf("Resetting queue ");
        q->front = q->rear = -1;
      }
      item = q->items[q->front];
      
  }
  return item;
}

void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue/Stack is empty");
  } else {
    printf("\nQueue/Stack contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%c ", int_to_ascii(q->items[i]));
    }
  }
}



//initializes matrix to 0
void init(int array[][GRAPHSIZE])
{
    int i,j;
    for(i = 0; i < GRAPHSIZE; i++)
        for(j = 0; j < GRAPHSIZE; j++)
            array[i][j] = 0;
}

//Add edge. set array[source][dest] = 1
void addEdge(int array[][GRAPHSIZE],int source, int dest)
{
     array[source][dest] = 1;
}

void printAdjMatrix(int array[][GRAPHSIZE])
{
     int i, j;
    printf("  A B C D E F\n");
     for(i = 0; i < GRAPHSIZE; i++) // prints the adj matrix
     {   printf("%c ", int_to_ascii(i));
         for(j = 0; j < GRAPHSIZE; j++)
         {
             printf("%d ", array[i][j]);
         }
         printf("\n");
     }
}

void BFS( int startVertex) {
  struct queue* q = createQueue();
  enqueue(q, startVertex);
  int currentVertex;
  int err = 0;
  do  {
    err++;
    if (err >50)
      break;
    
    currentVertex = dequeue(q);
    printQueue(q);
    printf("Visited %c\n", int_to_ascii(currentVertex));
    visited[currentVertex] = true;
    int i = 0;
    while (i < GRAPHSIZE){
        if (matrix[currentVertex][i] != 0){
            enqueue(q, i);
        }
        i++;

    }
    
    
  } while (currentVertex != (GRAPHSIZE-1));
}

void stack(struct queue* q, int value){
  if (q->rear == GRAPHSIZE - 1)
    printf("\nStack is Full!!");
  else {
    if (visited[value] != true){
    if (stacked[value] != true){
    if (q->front == -1)
      q->front = 0;
    
    for (int i = q->rear + 1; i > -1; i--){
      if (q->items[i] != NULL){
        q->items[i] = q->items[i - 1];
      }
    }
    q->rear++;

    q->items[q->front] = value;
    stacked[value] = true;
    }
    }
  }
}

int pop(struct queue* q){
  int item;
  if (isEmpty(q)) {
    printf("stack is empty");
    item = -1;
  } 
  else {
      item = q->items[q->front];
      while (visited[item] == true){
        dup_remove(q);
        item = q->items[q->front];
      }
    
      //q->front++;
      if (q->front > q->rear) {
        printf("Resetting queue ");
        q->front = q->rear = -1;
      }
      item = q->items[q->front];
      
  }
  dup_remove(q);
  return item;
}

void DFS(int startvertex){
  struct queue* q = createQueue();
  stack(q, startvertex);
  int currentVertex;
  int err = 0;
  do  {
    err++;
    if (err >50)
      break;
    
    printQueue(q);
    currentVertex = pop(q);
    
    printf("Visited %c\n", int_to_ascii(currentVertex));
    visited[currentVertex] = true;
    int i = 5;
    while (i != 0){
        if (matrix[currentVertex][i] != 0){
            stack(q, i);
        }
        i--;
    }
    
    
  } while (err != GRAPHSIZE);
}

int main(){
    

    init(matrix);
    addEdge(matrix, 0, 1);
    addEdge(matrix, 0, 3);
    addEdge(matrix, 0, 4);
    addEdge(matrix, 1, 2);
    addEdge(matrix, 1, 3);
    addEdge(matrix, 2, 1);
    addEdge(matrix, 4, 3);
    addEdge(matrix, 2, 3);
    addEdge(matrix, 3, 5);
    addEdge(matrix, 5, 2);

    printAdjMatrix(matrix);
    printf("BFS\n");
    BFS(0);
    for (int i = 0; i < GRAPHSIZE; i++){
      visited[i] = false;
    }
    printf("\n\nDFS \n");
    DFS(0);
    
    return 0;
}