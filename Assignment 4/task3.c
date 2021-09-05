#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//djikstra implementation inspired by https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
// and https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/?ref=lbp
struct stop {
    char location[300];
   
    
};


#define GRAPHSIZE 7667
#define stoplim 7668
struct stop stops[stoplim];
int next_field ( FILE *csv , int which);

int matrix[GRAPHSIZE][GRAPHSIZE];

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
int printSolution(int dist[], int n,int source, int destination) 
{ 
    
    printf("%d -> %d\n", source, destination);
    printf("Total\n%s -> %s = %d\n", stops[source].location , stops[destination].location, dist[destination]); 
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

void printroute(int used[],int destination){
    int i = used[destination];
    int j = destination;
    if(i == -1){
        return;
    }
    printroute(used, i);
    printf("\n%s -> %s = %d", stops[i].location, stops[j].location, matrix[j][i]);
    //printf("%d ", destination);
        

    
}

//https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
void dijkstra(int matrix[GRAPHSIZE][GRAPHSIZE], int source, int destination) 
{ 
    int used[GRAPHSIZE];
    int dist[GRAPHSIZE]; // The output array. 
    bool permanent[GRAPHSIZE]; // permanent[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 

    for (int i = 0; i < GRAPHSIZE; i++) {// Initialize all distances as INFINITE and permanent[] as false 
        dist[i] = INT_MAX;
        permanent[i] = false; 
        used[source] = -1;
    }
    
    dist[source] = 0; // Distance of source vertex from itself is always 0 
    used[source] = -1; 
    // Find shortest path for all vertices 
    for (int count = 0; count < GRAPHSIZE - 1; count++) { 
        int u = minDistance(dist, permanent); //start with min
        permanent[u] = true; // Mark the picked vertex as processed 

        for (int v = 0; v < GRAPHSIZE; v++) // Update dist value of the adjacent vertices of the picked vertex.
  
            // Update dist[v] only if is not in permanent, there is an edge from 
            // u to v, 
            if ((!permanent[v] && matrix[u][v]) && (dist[u] != INT_MAX) 
                && (dist[u] + matrix[u][v] < dist[v])){ // total weight of path from src to  v through u must be   smaller than current value of dist[v] 
                dist[v] = dist[u] + matrix[u][v]; 
                used[v] = u;
                }
    } 
    // print the constructed distance array 
    printroute(used, destination);
    printSolution(dist, GRAPHSIZE,source, destination); 
} 

int main(){
    init(matrix);
    FILE *csv;
    csv = (FILE *)malloc(sizeof(FILE));
    int n = 0;
    char duplicate[100] = {};
    csv = fopen("vertices.csv", "r"); 
    while(n != 2){
        n = next_field(csv,0);
        
        if (n == 1){
           // printf("\n\n");
        }
        if (n == 3){
           // printf("\n");
        }
        if (n == 2);
            //printf("\n\n\n");
    }
    fclose(csv);
    FILE *csv2;
    csv2 = (FILE *)malloc(sizeof(FILE));
    n = 0;
    csv2 = fopen("edges.csv", "r"); 
    while(n != 2){
        
        n = next_field(csv2,1);
        if (n == 1){
           //printf("\n\n");
        }
        if (n == 3){
            //printf("\n");
        }
    }

    fclose(csv2);
    dijkstra(matrix,300, 253);
    char  input1[10];
    char  input2[10];
    printf("\n enter two stop nos\n");
    gets( input1);
    gets( input2);
    int in1 = atoi(input1);
    int in2 = atoi(input2);

    dijkstra(matrix, in1,in2);


    printf("\n code over");
    return 0;

}

void stores(int no, char buffer[], int data){  //stores in struct from csv
    if (no != 0){ // ignores headings 
        switch (data)
        {
        case (1):
            for (int i = 0; i < 300; i++){
                stops[no].location[i] = buffer[i];
            }
            break;  
        default :

        break;
        }
    }
}

void storesedge(int no, char buffer[], int data){
    static int from;
    static int to;
    int weight;
    //printf("\ndata = %d , no = %d", data, no);
    if (no != 0){ // ignores headings 
        //printf("I'm in to stroreedge");
        switch (data)
        {
        case (0):
            from = atoi(buffer);
        
        break;
        case (1):
            to = atoi(buffer);
        
        break;
        case (2):
            weight = atoi(buffer);
            addEdge(from, to, weight);
        }
           



    }

}


int next_field ( FILE *csv , int which){    // reads from csv into buffer
    
    char buffer[300] = {0} ;
    bool quote = false;
    char c;
    static int no = 0; //4 data points 0-3
    static int data = 0;
    int n = 0;
    while(true){
        c = fgetc(csv);
        if (c == '"') quote = !quote;
        else if (c == EOF){
            //printf("%s", buffer);
            if (which == 0){
                stores( no, buffer, data);
                data = 0;
                no = 0;
            }
            else {
                storesedge(no,buffer,data);
                printf("\nand for that reason,I'm out\n");
            }
            return 2;
        }
        else if ((c == ',') && (quote == false)){
            //printf("%s", buffer);
            if (which == 0){
                stores( no, buffer, data);
            }
            else {
                storesedge(no,buffer,data);
            }
            data++;
            return 3;
        }
        else if (c == '\n'){
            //printf("%s", buffer);
            if (which == 0){
                stores(no, buffer, data);
            }
            else {
                storesedge(no,buffer,data);
            }
            no++;
            data = 0;
            return 1;
        }
        else {
            buffer[n] = c;
            n++;
        }

    }
}
