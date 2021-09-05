//Alex Cooper
//student no: 18320408
//date 04/10/2020

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//When a hash function maps two different keys to the same table address, a collision is said to occur.





struct hash {
    struct hash *next;
    char Did[60];
    long Pid;
    char forename[60];
    char surname[60];
    long freq;
    int age;
    char type[60];
    char gender[60];
    char nation[60];
    char religion[60];
    char job[60];
    struct hash *prev;
    
};
void free_me();
int next_field ( FILE *csv);
void print_table();
int double_hash(char buffer[]);
void store( long no, char buffer[], int data);
void stores( long no, char buffer[], int data);

struct hash table[61000];
long ARRAY_SIZE = 61000;
long collisons = 0;
long terms = 0;
long term = 0;



int hash1(char* s){
    unsigned int hash = 0;
    while(*s){
        hash = (31 +  hash + *s );
        s++;
    }
    return (hash % ARRAY_SIZE);
}

int hash2(char *s){
    unsigned int hash = 0;
    while(*s){
        hash = (hash + *s );
        s++;
    }
    return (ARRAY_SIZE - (hash % ARRAY_SIZE));
}


    struct hash *temp;
    
int main(){
    FILE *csv;
    csv = (FILE *)malloc(sizeof(FILE));
    temp = (struct hash*)malloc( sizeof(struct hash ));
    const int max_len = 30;
    int n = 0;
    char input[30];
    int inputdex;

    for (int i = 0; i<ARRAY_SIZE; i++){
        table[i].next = NULL;
    }
    csv = fopen("people.csv", "r"); // people.csv is a large boi
    while(n != 2){
        n = next_field(csv);
        
        if (n == 1){
            //printf("\n\n");
        }
        if (n == 3){
            //printf("\n");
        }
    }

    fclose(csv);
    //print_table();
    printf("\ntotal input terms: %d", term);
    printf("\ntotal unique terms: %d\ntotal collisions: %d \n", terms, collisons);
    float load =  (float)terms / (float)ARRAY_SIZE;
    printf("capacity: %d\nload: %f\n",ARRAY_SIZE, load);
    printf("Enter Search i guess: \n");
    gets(input);
    
    while (strcmp(input, "quit") != 0){
        inputdex = double_hash(&input[0]);
        while (strcmp(table[inputdex].surname,input) != 0){
            n++;
            if (inputdex == 99)
                inputdex = 0;
            else inputdex++;
            if (n > 103){
                printf("\nwhy would you do this? incorrect search parameter.\n");
                break;
            }
        }
        struct hash *temp2;
        temp2 = (struct hash*)malloc( sizeof(struct hash ));
        struct hash *next;
        next = (struct hash*)malloc( sizeof(struct hash ));
        temp2 = &table[inputdex];
        printf("frequency: %d\n", table[inputdex].freq);
        while (temp2 != NULL){
            printf("\n%d  %s  %s  %s  %d  %s  %s  %s  %s " , temp2->Pid, temp2->Did, temp2->surname, temp2->forename, temp2->age, temp2->type, temp2->gender, temp2->nation, temp2->religion, temp2->job);
            next = temp2->next;
            temp2 = next;
        }
        printf("Enter search term or \"quit\"\n");
        gets(input);
    }
    free_me();
    
    return 0;
}

void store( long no, char buffer[], int data){
    struct hash *temp2;
    temp2 = (struct hash*)malloc( sizeof(struct hash ));
    struct hash *next;
    next = (struct hash*)malloc( sizeof(struct hash ));
    struct hash *prev;
    prev = (struct hash*)malloc( sizeof(struct hash ));
    int index;
    if (no != 0){
        term++;
        index = double_hash(temp->surname);
        //printf("\nhash is %d", index);
        if (strcmp(table[index].surname, temp->surname) == 0){
            //printf("link da list innit");
            table[index].freq++;
            temp2 = &table[index];
            prev = NULL;
            while (temp2 != NULL){
                next = temp2->next;
                prev = temp2;
                temp2 =  next;
                //printf("oh no");
            }
            temp2 = (struct hash*)malloc( sizeof(struct hash ));
            prev->next = temp2;
            for (int i = 0; i < 60; i++){
                temp2->Did[i] = temp->Did[i];
                temp2->surname[i] = temp->surname[i];
                temp2->forename[i] = temp->forename[i];
                temp2->gender[i] = temp->gender[i];
                temp2->nation[i] = temp->nation[i];
                temp2->type[i] = temp->type[i];
                temp2->religion[i] = temp->religion[i];
                temp2->job[i] = temp->job[i];
            }
            temp2->Pid = temp->Pid;
            temp2->age = temp->age;
            temp2->next = NULL;
            
            //collisons++;  not really a collision since hash works correctly.
        }   
        else if(table[index].surname[0] == 0){
            //printf("\n Empty cell");
            table[index] = *temp;
            table[index].freq++;
            terms++;
           
        }
    }
    
}

void stores(long no, char buffer[], int data){
    if (no != 0){ // ignores headings 
        switch (data)
        {
        case (0):
            temp->Pid = atoi(buffer);
            break;
        
        case (1):
            for (int i = 0; i < 60; i++){
                temp->Did[i] = buffer[i];
            }
            break;
        case (2):
            for (int i = 0; i < 60; i++){
                temp->surname[i] = buffer[i];
            }
            break;
        
        case (3):
            for (int i = 0; i < 60; i++){
                temp->forename[i] = buffer[i];
            }
            break;
        
        case (4):
            temp->age = atoi(buffer);
            
            break;

        case (5):
            for (int i = 0; i < 60; i++){
                temp->type[i] = buffer[i];
            }
            break;

        case (6):
            for (int i = 0; i < 60; i++){
                temp->gender[i] = buffer[i];
            }
            break;

        case (7):
            for (int i = 0; i < 60; i++){
                temp->nation[i] = buffer[i];
            }
            break;

        case (8):
            for (int i = 0; i < 60; i++){
                temp->religion[i] = buffer[i];
            }
            break;

        case (9):
            for (int i = 0; i < 60; i++){
                temp->job[i] = buffer[i];
            }
            temp->next = NULL;
            break;
        }
    }
}

int double_hash(char buffer[]){
    int index; 
    int i = 0;
    index = hash1(&buffer[0]) % ARRAY_SIZE ;
    if ((strcmp(table[index].surname, buffer) != 0) && (table[index].surname[0] != 0)){
        collisons++;
        //printf("    %d collision\n", index);
    }
    while ((strcmp(table[index].surname, buffer) != 0) && (table[index].surname[0] != 0)){
        i++;
        index = (hash1(&buffer[0]) + (i * hash2(&buffer[0]))) % ARRAY_SIZE ;
        if (i > 50)
            break;
    }
    return index;
}

int next_field ( FILE *csv){
    
    char buffer[60] = {0} ;
    bool quote = false;
    char c;
    static long no = 0; //11 data points 0-10
    static int data = 0;
    int n = 0;
    while(true){
        c = fgetc(csv);
        if (c == '"') quote = !quote;
        else if (c == EOF){
            //printf("%s", buffer);
            store( no, buffer, data);

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
            stores( no, buffer, data);
            store(no, buffer, data);
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

void print_table(){
    for (int i = 0; i < ARRAY_SIZE; i++){
        printf("\n %d   %s",i , table[i].surname);
    }
}

void free_me(){
    struct hash *temp2;
    temp2 = (struct hash*)malloc( sizeof(struct hash ));
    struct hash *next;
    next = (struct hash*)malloc( sizeof(struct hash ));
    
    for (long i = 0; i < ARRAY_SIZE; i++){
        temp2 = &table[i];
        while (temp2->next != NULL){
            struct hash *del;
            next = temp2->next;
            del = temp2;
            temp2 =  next;
            free(del);
            
        }

    }
    free(temp2);
    free(next);
    printf("\nFinally I am free! \nUnless....");
}