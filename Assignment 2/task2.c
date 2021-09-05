#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARRAY_VAL  10000
#define RAND_MAX 32767  // for duplicate checking
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
        //swaps array indices
}


void insertsort(int **array[], int low, int high){          // insertsort using swap function 
    for (int pass = 0; pass < high ; pass++){
        for (int i = pass + 1; i > 0; i--){
            comparisons++;
            if (array[i - 1] > array[i]){
                swap(array, i - 1, i);
            }
        }
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
    gen_array(array, input);
    insertsort(array, p, r);

    printf("\nsorted array:");
    for (int i = 0; i<MAX_ARRAY_VAL; i++){
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
    long duplicate[RAND_MAX]= {}; // array for duplicate checking
    switch (type){
        case (1):
            while (array[MAX_ARRAY_VAL - 1] == NULL){       // array with no duplicates
                
                dup = rand();
                
                if (duplicate[dup] == NULL){
                    array[i] = dup;
                    duplicate[dup] = dup;
                    i++;
                }
            }
            break;

        case (2):
            while (array[MAX_ARRAY_VAL - 1] == NULL){       // array with duplicates
                
                dup = rand();
                
                array[i] = dup;
                i++;
                
            }
            break;

        case (3):
            for (int i = 0 ;i < MAX_ARRAY_VAL; i++){        // array ascending sorted

                array[i] = i;
                
            }
            break;

        case (4):
            for (int j = MAX_ARRAY_VAL-1 ;j > -1; j--){     // array decending sorted
                array[i] = j;
                i++;
            }
            break;

        case (5):                                           // uniform array
            dup = rand();
            for (i = 0; i < MAX_ARRAY_VAL; i++){
                array[i] = dup;
            }
            break;
    }

}