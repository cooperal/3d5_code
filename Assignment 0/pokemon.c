//Alex Cooper
//student no: 18320408
//date 04/10/2020

#include <stdio.h>
#include <stdbool.h>

void store(int data, int no, char buffer[]);
int next_field ( FILE *csv );

struct pokemon {
    int no;
    char name[20];
    char type[20];
    char type2[20];
    int total;
    int attack;
    int hp;
    int defence;
    int spatk;
    int spdef;
    int speed;
    int gen;
    bool legend;
    char desc[150];
};

struct pokemon pokemon[650];

int main(){
    FILE *csv;
    const int max_len = 30;
    int n = 0;
    int total = 0;
    int m , average = 0;
    int normno = 0;
    int normtotal = 0;
    int normavg = 0;
    int psyno = 0;
    int psyavg = 0;
    int psytotal = 0;
    csv = fopen("pokemon.csv", "r");
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
    
    for (int i = 1; i < 650; i++){
        total += pokemon[i].attack;
        
        if (strncmp(pokemon[i].type, "Normal") == 0){
            normtotal += pokemon[i].total;
            normno++;
        }
        if (strncmp(pokemon[i].type, "Psychic") == 0){
            psytotal += pokemon[i].total;
            psyno++;
        }
    }
    average = total / 649;
    normavg = normtotal / normno;
    psyavg = psytotal / psyno;
    printf("\n\nthe average attack of all pokemon is %d" , average);
    printf("\nThe average total of normal pokemon is %d" , normavg);
    printf("\nThe average total of Psychic pokemon is %d" , psyavg);
    return 0;
}

void store(int data, int no, char buffer[]){
    if (no != 0){ // ignores headings 
        switch (data)
        {
        case (0):
            pokemon[no].no = no;
            break;
        
        case (1):
            for (int i = 0; i < 20; i++){
                pokemon[no].name[i] = buffer[i];
            }
            break;
        case (2):
             for (int i = 0; i < 20; i++){
                pokemon[no].type[i] = buffer[i];
            }
            break;
        
        case (3):
             for (int i = 0; i < 20; i++){
                pokemon[no].type2[i] = buffer[i];
            }
            break;
        
        case (4):
            pokemon[no].total = atoi(buffer);
            
            break;

        case (5):
            pokemon[no].attack = atoi(buffer);
            break;

        case (6):
            pokemon[no].hp = atoi(buffer);
            break;

        case (7):
            pokemon[no].defence = atoi(buffer);
            break;

        case (8):
            pokemon[no].spatk = atoi(buffer);
            break;

        case (9):
            pokemon[no].spdef = atoi(buffer);
            break;
        
        case(10):
            pokemon[no].speed = atoi(buffer);
            break;

        case (11):
            pokemon[no].gen = atoi(buffer);
            break;

        case (12): 
            if (buffer == "False"){
            pokemon[no].legend = false;
            }
            else pokemon[no].legend = true;
            break;
        
        case (13):
             for (int i = 0; i < 150; i++){
                pokemon[no].desc[i] = buffer[i];
            }
            break;
        }

    }
}

int next_field ( FILE *csv ){
    char buffer[150] = {0} ;
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
            store(data, no, buffer);
            return 2;
        }
        else if ((c == ',') && (quote == false)){
            printf("%s", buffer);
            store(data, no, buffer);
            data++;
            return 3;
        }
        else if (c == '\n'){
            printf("%s", buffer);
            store(data, no, buffer);
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