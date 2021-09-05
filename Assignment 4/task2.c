#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//djikstra implementation inspired by https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/

#define GRAPHSIZE 7



int matrix[GRAPHSIZE][GRAPHSIZE];

char int_to_ascii(int i){
    int a;
    if ((i < 26) && (i >= 0)){          //converts an int to a capital letter in ascii
        return i + 65;
    }

    else
    {
        printf("err: int is not meant to be a char");
    }
    
}


void init(int array[][GRAPHSIZE])
{
    int i,j;
    for(i = 0; i < GRAPHSIZE; i++)
        for(j = 0; j < GRAPHSIZE; j++)      
            array[i][j] = 0;
}

void addEdge(int source, int dest ,int weight)
{
     matrix[source][dest] = weight;     // fills array with two way edge given values

     matrix[dest][source] = weight;
}

void printAdjMatrix(int array[][GRAPHSIZE])
{
     int i, j;
    printf("  A  B  C  D  E  F  G\n");
     for(i = 0; i < GRAPHSIZE; i++) // prints the adj matrix
     {   printf("%c ", int_to_ascii(i));
         for(j = 0; j < GRAPHSIZE; j++)
         {
             printf("%d  ", array[i][j]);
         }
         printf("\n");
     }
}

int printSolution(int dist[], int n) 
{ 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < GRAPHSIZE; i++) 
        printf("A -> %c = %d\n", int_to_ascii(i), dist[i]); 
} 

int minDistance(int dist[], bool permanent[]) 
{ 
    int min = INT_MAX;
    int min_index; 
  
    for (int i = 0; i < GRAPHSIZE; i++) 
        if (permanent[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i; 
        }
  
    return min_index; 
} 
//https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
void dijkstra(int matrix[GRAPHSIZE][GRAPHSIZE], int src) 
{ 
    int dist[GRAPHSIZE]; // The output array. 
    bool permanent[GRAPHSIZE]; // permanent[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 

    for (int i = 0; i < GRAPHSIZE; i++) {// Initialize all distances as INFINITE and permanent[] as false 
        dist[i] = INT_MAX;
        permanent[i] = false; 
    }
    
    dist[src] = 0; // Distance of source vertex from itself is always 0 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < GRAPHSIZE - 1; count++) { 
        int u = minDistance(dist, permanent); //start with min
        permanent[u] = true; // Mark the picked vertex as processed 
        for (int v = 0; v < GRAPHSIZE; v++) // Update dist value of the adjacent vertices of the picked vertex.
  
            // Update dist[v] only if is not in permanent, there is an edge from 
            // u to v, 
            if ((!permanent[v] && matrix[u][v]) && (dist[u] != INT_MAX) 
                && (dist[u] + matrix[u][v] < dist[v])) // total weight of path from src to  v through u must be   smaller than current value of dist[v] 
                dist[v] = dist[u] + matrix[u][v]; 
    } 
    // print the constructed distance array 
    printSolution(dist, GRAPHSIZE); 
} 


int main(){
    init(matrix);

    addEdge(0,1,1);
    addEdge(0,2,3);
    addEdge(0,5,10);
    addEdge(1,2,1);
    addEdge(1,3,7);
    addEdge(1,4,5);
    addEdge(1,6,2); // creating adjacency array
    addEdge(2,3,9);
    addEdge(2,4,3);
    addEdge(3,4,2);
    addEdge(3,6,12);
    addEdge(3,5,1);
    addEdge(4,5,2);

    printAdjMatrix(matrix);

    dijkstra(matrix, 0);

    return 0;
}