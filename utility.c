#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>

#define MEMSIZE 100

/* Input/Output */
#define READ   10
#define WRITE  11

/* Loading/Storing */
#define LOAD  20
#define STORE 21

/* Arithmetical */
#define ADD      30
#define SUBTRACT 31
#define DIVIDE   32
#define MULTIPLY 33

/* Reference and control */
#define BRANCH     40
#define BRANCHNEG  41
#define BRANCHZERO 42
#define HALT       43

int load_file(char *file, int *memory){
  int ins, instructionCounter;
  ins = instructionCounter = 0;
  FILE *filePtr;
  if((filePtr = fopen(file, "r")) != NULL) {

    while(!feof(filePtr)) {
        fscanf(filePtr,"%d", &ins);
        memory[instructionCounter] = ins;
        printf("Instruction = %d\n", ins);
        instructionCounter++;
		}

  } else {
    return 1;
  }

  fclose(filePtr);

	return 0;
}

void execution(int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand, int *memory){
  int halt, forceQuit;
  halt = forceQuit = 0;

  while (halt == 0){

    //fetch
    *instructionRegister = memory[*instructionCounter];

    //solve in operation code and operend
    *operationCode = *instructionRegister / 100;
    *operand = *instructionRegister % 100;
    //print the value of the operation code and the operend
    printf("operationCode = %02d\n", *operationCode);
    printf("operand = %02d\n", *operand);

    //check op code
    switch (*operationCode) {
      case READ:
        puts("Please enter Input ");
        scanf("%d", &memory[*operand]);
        break;
      case WRITE:
        puts("WRITE RESULT:********"); 
        printf("%d\n", memory[*operand]);
        puts("********");
        break;
      case LOAD:
        puts("loading");
        *accumulator = memory[*operand];
        break;
      case STORE:
        puts("storing");
        memory[*operand] = *accumulator;
        break;
      case ADD:
        puts("adding");
        *accumulator += memory[*operand];
        break;
      case SUBTRACT:
        puts("subtracting");
        *accumulator -= memory[*operand];
        break;
      case DIVIDE:
        puts("dividing");
        if (memory[*operand] != 0){
            *accumulator /= memory[*operand];
        }else{
          printf("Execution error, terminating now\n");
          halt = 1;
        }
        break;
      case MULTIPLY:
        puts("multiplying");
        *accumulator *= memory[*operand];
        break;
      case BRANCH:
        puts("branching");
        *instructionCounter = *operand - 1;
        break;
      case BRANCHNEG:
        puts("branchNeg");
        if (*accumulator < 0){
          *instructionCounter = *operand - 1;
        }
        break;
      case BRANCHZERO:
        puts("BranchZero");
        if (*accumulator == 0){
          *instructionCounter = *operand - 1;
        }
        break;
      case HALT:
        halt = 1;
        printf("%s", "*** Simpletron execution terminated ***\n");
        break;
      default:
        printf("Runtime Error: the operation code (%d) in memory address %d isn't allowed.\n", *operationCode, *operand);
        printf("Would you like to terminate execution now? 1 = yes, 0 = no\n");
        scanf("%d", &forceQuit);
        if (forceQuit == 1){
          halt = 1;
          printf("%s", "*** Simpletron execution terminated ***\n");
        }
    }
    //end operation phase
    *instructionCounter += 1;
	printResult( accumulator, instructionCounter, instructionRegister, operationCode, operand, memory);
  }
  //end of while loop
}


void printResult(int *acc, int *counter, int *iR, int *opCode, int *operand, int *memory){
  int i, j, z;
  i = j = z = 0;
  puts("REGISTERS:");
  printf("accumulator = \t\t%+04d\n", *acc);   //print the value of accumulator
  printf("instructionCounter = \t%02d\n", *counter);  //print the value of instruction count
  printf("instructionRegister = \t%+04d\n", *iR); //print the value of instruction register
  printf("operationCode =\t\t%02d\n", *opCode); //print the value of operation code
  printf("operand = \t\t%02d\n", *operand);   //print the value of operand
  puts("");
  puts("MEMORY");
  //11 rows & 11 columns

  for(z = 0; z < 1; z++){
      printf("  ");
      for (i = 0; i < 11; i++){
        for (j = 0; j < 11; j++){
            //column headers then row headers (row head is j == 0)
            if( i == 0){
              if( j < 10){
                printf("\t%d", j);
              }
              //row headers?
            }else if(j == 0){
              printf("%3d", (i-1)*10 + (z * 100) );
              //mem blocks
            }else{
              printf("\t%+05d", memory[ ((i-1)*10)+ j-1 + (z * 100)]);
            }
        }
        puts("");
      }
      puts("");
  }
}
