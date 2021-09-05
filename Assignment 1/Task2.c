//Alex Cooper
//student no: 18320408
//date 04/10/2020

#include <stdio.h>
#include <stdbool.h>

//When a hash function maps two different keys to the same table address, a collision is said to occur.


void store( int no, char buffer[]);
int next_field ( FILE *csv );

struct hash {
    int no;
    char name[30];
    int freq;
    
};

struct hash table[100];
int ARRAY_SIZE = 100;
int collisons = 0;
int terms = 0;
int term = 0;


int hash(char* s){
    int hash = 0;
    while(*s){
        hash = (31 +  hash + *s );
        s++;
    }
    return (hash % ARRAY_SIZE);
}

int main(){
    FILE *csv;
    const int max_len = 30;
    int n = 0;
    char input[30];
    int inputdex;

    csv = fopen("names.csv", "r");
    while(n != 2){
        n = next_field(csv);
        
        if (n == 1){
            printf("\n\n");
        }
        if (n == 3){
            printf("\n");
        }
    }
    fclose(csv);
    print_table();
    printf("\ntotal input terms: %d", term);
    printf("\ntotal unique terms: %d\ntotal collisions: %d \n", terms, collisons);
    float load =  (float)terms / (float)ARRAY_SIZE;
    printf("capacity: %d\nload: %f\n",ARRAY_SIZE, load);
    printf("Enter Search i guess: \n");
    gets(input);
    
    while (strcmp(input, "quit") != 0){
        inputdex = hash(&input);
        while (strcmp(table[inputdex].name,input) != 0){
            n++;
            if (inputdex == 99)
                inputdex = 0;
            else inputdex++;
            if (n > 103){
                printf("\nwhy would you do this? incorrect search parameter.\n");
                break;
            }
        }
        printf("frequency: %d\n", table[inputdex].freq);
        printf("Enter search term or \"quit\"\n");
        gets(input);
    }

    
    
    return 0;
}

void store( int no, char buffer[]){
    term++;
    char *s;
    int index;
    bool same = false;
    index = hash(&buffer[0]);
    printf("\n %d", index);
    if (strcmp(table[index].name, buffer) == 0){
        table[index].freq++;
        //collisons++;  not really a collision since hash works correctly.
    }
    else if(table[index].name[0] == 0){
        printf("\n Empty cell");
        for (int i = 0; i<30; i++)
            table[index].name[i] = buffer[i];
        table[index].freq++;
        terms++;
    }
    else {
        printf("collision");
        collisons++;
        while (table[index].name[0] != 0){
            if (strcmp(table[index].name, buffer) != 0){
                if (index == 99){
                    index = 0;
                }
                else index++;
                
        

            }
            if (strcmp(table[index].name, buffer) == 0){
                table[index].freq++;
                same = true;
                break;
                
            }
             
        }
        if (!same){
            for (int i = 0; i<30; i++)
                table[index].name[i] = buffer[i];
            table[index].freq++;
            terms++;
        }
    }
    
}

int next_field ( FILE *csv ){
    char buffer[30] = {0} ;
    bool quote = false;
    char c;
    static int no = 0; //14 data points 0-13
    static int data = 0;
    int n = 0;
    while(true){
        c = fgetc(csv);
        if (c == '"') quote = !quote;
        else if (c == EOF){
            printf("%s", buffer);
            store( no, buffer);
            return 2;
        }
        else if ((c == ',') && (quote == false)){
            printf("%s", buffer);
            store( no, buffer);
            return 3;
        }
        else if (c == '\n'){
            printf("%s", buffer);
            store( no, buffer);
            no++;
            return 1;
        }
        else {
            buffer[n] = c;
            n++;
        }

    }
}

void print_table(){
    for (int i = 0; i < ARRAY_SIZE; i++){
        printf("\n %d   %s",i , table[i].name);
    }
}