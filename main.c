/*-------------------------------------------
Program 1: Elementary Cellular Automaton
Course: CS 211, Fall 2023, UIC
System: Advanced zyLab
Author: Ayooluwa Adeleye
------------------------------------------- */

//Elementary Cellular Automaton

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000]
//   ex: rule = 30 = 00011110 -> [01111000]
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {

    //TODO: Task 1 - write the setBitArray() function

    // Check if the rule is within the valid range (0-255)
    if (rule < 0 || rule > 255)
        return false;

    // Handle the case where rule = 0
    if (rule == 0){
        for (int i = 0; i < 8; i++) {
            bitArray[i] = 0;
        }
        return true;
    }

    // Converting the rule to a binary bit array (stored in reverse order)
    int i = 0;
    while(rule > 0){
        bitArray[i] = rule % 2;
        i++;
        rule = rule / 2;
    }

    return true;
}

//convert a 3-bit state array to its
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
int stateToIndex(bool state[3]) {

    //TODO: Task 4 - write the stateToIndex() function
    int index = 0;

    // Convert the 3-bit state array to an index
    for (int i=0; i<3; i++){
        index = index*2 + state[i];
    }
    return index;
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping
void setStates(cell world[WORLD_SIZE]) {

    //TODO: Task 5 - write the setStates() function

    for (int i = 0; i < WORLD_SIZE; i++ ){
        // Update the state array for each cell based on its neighbors
        world[i].state[0] = world[i-1].active;
        world[i].state[1] = world[i].active;
        world[i].state[2] = world[i+1].active;
    }

    //Handle the boundary conditions of the world cycle
    for (int i = 0; i < WORLD_SIZE; i++ ){
        world[WORLD_SIZE-1].state[2] = world[0].active;
        world[0].state[0] = world[WORLD_SIZE-1].active;
    }
    return;
}

//evolve each cell's active status to the next generation
//  using its state array
//ruleBitArray contains the 8-bits for the rule#,
//  stored in reverse order
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {

    //TODO: Task 7 - write the evolveWorld() function

    cell newWorld[WORLD_SIZE];

    // Iterate through each cell in the world
    for (int i = 0; i < WORLD_SIZE; i++){
        // Calculate the index for the ruleBitArray based on the cell's state
        int index = stateToIndex(world[i].state);

        // Update the new world based on the ruleBitArray
        newWorld[i].active = ruleBitArray[index];
    }

    //Copy to the new world back to the original world
    for (int i = 0; i< WORLD_SIZE; i++){
        world[i].active = newWorld[i].active;
    }
    return;
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //TODO: Task 2 - read in a valid rule# and
    //      generate the rule's 8-bit rule bit array
    //      print the bit array in correct binary number order

    // Read in a valid rule number and generate the rule's 8-bit ruleBitArray
    int rule;
    bool bitArray[8];
    do{
        printf("Enter the rule # (0-255): ");
        scanf("%d", &rule);
    }while(!(setBitArray(bitArray, rule)));

    printf("\n");
    printf("The bit array for rule #%d is ", rule);
    for (int i = 7; i >= 0; i--) {
        printf("%d", bitArray[i]);
    }
    printf("\n");


    //TODO: Task 3 - use the rule bit array to report the evolution
    //      step for all possible cell states.
    //      follow the format of the sample output exactly

    // Report the evolution step for all the possible cell states
    printf("The evolution of all possible states are as follows:\n");
    printf("|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n");
    for (int i = 7; i >= 0; i--){
        if (bitArray[i]  == 1){
            printf(" |*|  ");
        }else{
            printf(" | |  ");
        }
        if(i != 0){
            printf("  ");
        }

    }
    printf("\n");

    //TODO: Task 6 - read in the total number of generation evolution
    //      steps from the user and initialize the world with ONLY the
    //      middle cell active, all other cells should be inactive;
    //      make sure to set the state array for each cell.


    // Read in the total number of generation evolution steps from the user
    // and initialize the world with only the middle cell active
    int numGenerations;
    printf("Enter the number of generations: \n");
    scanf("%d", &numGenerations);

    for (int i = 0; i < WORLD_SIZE; i++){
        world[i].active = false;
    }

    world[WORLD_SIZE / 2].active = true;
    setStates(world);

    printf("Initializing world & evolving...\n");

    // Evolve the world for the speciied number of generations
    for (int i = 0; i< WORLD_SIZE; i++){
        if (world[i].active){
            printf("*");
        }else{
            printf(" ");
        }
    }
    printf("Initializing world & evolving...\n");

    //TODO: Task 8 - evolve the world the user-specified number
    //      of generations, printing each active cell as '*' and
    //      each non-active cell as ' ' (whitespace) after each
    //      evolution step to the next generation
    for (int generation = 0; generation < numGenerations; generation++){
        for (int i = 0; i< WORLD_SIZE; i++){
            if (world[i].active){
                printf("*");
            }else{
                printf(" ");
            }
        }
        printf("\n");
        evolveWorld(world, bitArray);
        setStates(world);
    }
    return 0;
}
