#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARRAY_VAL  10000    
#define RAND_MAX 32767      //used for array generator

long swaps = 0;
long comparisons = 0;

void gen_array(int ** array[], int type);

void swap(int **array[], int low, int high){
    int templ;
    int temph;
    templ = array[low];
    temph = array[high];
    array[high] = templ;
    array[low] = temph;
    swaps++;
    // does what it says on the tin
}

int partition(int **array[], int start, int end){
    if (start == end)
        return start;
    int pivot = array[end];
    int low = start-1;
    int high = end;
    for(;;){
        do{
            low++;
            comparisons++;
            if (low == end) break;
            comparisons++;
        }while(array[low] < pivot);
        
        do{
            high--;
            comparisons++;
            if(high == start)break;
            comparisons++;
        }while (array[high] > pivot);
        comparisons++;
        if(low>=high){
            comparisons++;
            if (low != end){
                swap(array,low,end);
            }
            return low;
        }
        // Hoare partitioning function from lectures 
        comparisons++;
        if (low != high){
            swap(array, low, high);
        }
    }
}

void quicksort(int **A[], int p, int r ){
    int q = 0;
    if (p < r){
        q = partition( A, p, r );
        quicksort( A, p, q - 1 );
        quicksort( A, q + 1, r );       //quicksort function from lectures
    }
}





int main(){
    long array[MAX_ARRAY_VAL] = {};
    long p = 0;
    long r = MAX_ARRAY_VAL-1;
    char inputc[2];
    int input;
    printf("Enter array type ro be tested.\n1 = rand no duplicates.\n2 = rand with duplicates.\n3 = ascending sorted.\n4 = descending sorted.\n5 = uniform\n");
    gets(inputc);
    input = atoi(inputc);
    gen_array(array, input);    // uses input to generate array to be sorted 
    quicksort(array, p, r);     //sorts

    printf("\nsorted array:");
    for (int i = 0; i<MAX_ARRAY_VAL; i++){          //prints array
        printf(" %u ", array[i]);
        if ((i % 30) == 0)
            printf("\n");
    }
    printf("\ntotal swaps: %d", swaps);
    printf("\ntotal comparisons: %d", comparisons);
    
    return 0;
}

void gen_array(int ** array[], int type) {
    srand(time(0));
    int i = 0;
    long dup = 0;
    long duplicate[RAND_MAX]= {};   // array for duplicate checking
    switch (type){
        case (1):
            while (array[MAX_ARRAY_VAL - 1] == NULL){
                
                dup = rand();
                
                if (duplicate[dup] == NULL){ // if the duplicate array is not emtpty in the numbers position its a duplicate
                    array[i] = dup;
                    duplicate[dup] = dup;
                    i++;
                }
            }
            break;

        case (2):
            while (array[MAX_ARRAY_VAL - 1] == NULL){
                
                dup = rand();
                
                array[i] = dup;
                i++;
                
            }
            break;

        case (3):
            for (int i = 0 ;i < MAX_ARRAY_VAL; i++){

                array[i] = i;               // assigns ordered array
                //printf( " %d ", array[i]);
            }
            break;

        case (4):
            for (int j = MAX_ARRAY_VAL-1 ;j > -1; j--){
                array[i] = j;               // assigns reverse ordered array
                i++;
            }
            break;

        case (5):
            dup = rand();
            for (i = 0; i < MAX_ARRAY_VAL; i++){
                array[i] = dup;                 // picks a random number for uniform array
            }
            break;
    }

}