#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_VAL  19000
long swaps = 0;
long comparisons = 0;
int tens = 0;

struct game {
    char title[100];
    char platform[100];
    int score;
    int release_year;
    
};
struct game table[MAX_ARRAY_VAL] = {};      // global array of structs 
void gen_array(int ** array[], int type);

void swap( int low, int high){
    struct game templ;
    struct game temph;          //swap function now uses global struct array and swaps structs
    templ = table[low];
    temph = table[high];
    table[high] = templ;
    table[low] = temph;
    swaps++;

}

int partition( int start, int end){
    if (start == end)
        return start;
    int pivot = table[end].score;
    int low = start-1;
    int high = end;
    for(;;){
        do{
            low++;
            comparisons++;
            if (low == end) break;
            comparisons++;
        }while(table[low].score < pivot);
        
        do{
            high--;
            comparisons++;
            if(high == start)break;
            comparisons++;
        }while (table[high].score > pivot);
        comparisons++;
        if(low>=high){
            comparisons++;
            if (low != end){
                swap(low,end);
            }
            return low;
        }
        comparisons++;
        if (low != high){
            swap(low, high);
        }
    }
}

void quicksort( int p, int r ){
    int q = 0;
    if (p < r){
        q = partition( p, r );
        quicksort( p, q - 1 );
        quicksort(  q + 1, r );
    }
}



void stores(long no, char buffer[], int data){  //stores in struct from csv
    if (no != 0){ // ignores headings 
        switch (data)
        {
        case (0):
            for (int i = 0; i < 100; i++){
                table[no].title[i] = buffer[i];
            }
            break;
        
        case (1):
            for (int i = 0; i < 100; i++){
                table[no].platform[i] = buffer[i];
            }
            break;
        case (2):
            table[no].score = atoi(buffer);
            if (table[no].score == 10)
                tens++;
            break;
        
        case (3):
            table[no].release_year = atoi(buffer);
            break;
        }
    }
}

int next_field ( FILE *csv){    // reads from csv into buffer
    
    char buffer[100] = {0} ;
    bool quote = false;
    char c;
    static long no = 0; //4 data points 0-3
    static int data = 0;
    int n = 0;
    while(true){
        c = fgetc(csv);
        if (c == '"') quote = !quote;
        else if (c == EOF){
            //printf("%s", buffer);
            stores( no, buffer, data);

            return 2;
        }
        else if ((c == ',') && (quote == false)){
            //printf("%s", buffer);
            stores( no, buffer, data);
            data++;
            return 3;
        }
        else if (c == '\n'){
            //printf("%s", buffer);
            stores(no, buffer, data);
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



int main(){
    long p = 0;
    long r = MAX_ARRAY_VAL-1;
    FILE *csv;
    csv = (FILE *)malloc(sizeof(FILE));
    int n = 0;
    char duplicate[100] = {};
    csv = fopen("ign.csv", "r"); 
    while(n != 2){
        n = next_field(csv);
        
        if (n == 1){
           // printf("\n\n");
        }
        if (n == 3){
           // printf("\n");
        }
    }

    fclose(csv);
    quicksort( p, r);
    printf("\nTitle  Platform  Score  Year\n");
    
    int i = MAX_ARRAY_VAL-1;
    for (int j = 0; j<10; j++){                                     // should print top ten list
        while (strcmp(table[i].title, duplicate) == 0){             // attempting to remove duplicate games from top ten list, ineffective
            i--;
            
        }
        printf("%s\n%s\n%d\n%d\n\n",table[i].title, table[i].platform, table[i].score, table[i].release_year);
        for (int k = 0; k<100; k++){
            duplicate[k] = table[i].title[k];
        }
        i--;
    }

    
    printf("\nnumber of games that recieved a score of 10: %d", tens);
    printf("\ntotal swaps: %d", swaps);
    printf("\ntotal comparisons: %d", comparisons);
    
    return 0;
}

