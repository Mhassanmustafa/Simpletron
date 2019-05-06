#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#define MEMSIZE 100

int memory[MEMSIZE];
int load_file(char *file, int *memory);

int main(int argc, char** argv){

  int instructionCounter, operationCode, operand;
  signed int accumulator, instructionRegister;

  accumulator = instructionRegister = +0000;
  operationCode = 00;
  instructionCounter = operand = 000;

  int *instructionCounterPtr, *operationCodePtr, *operandPtr;
  signed int *accumulatorPtr, *instructionRegisterPtr;


  instructionCounterPtr = &instructionCounter;
  operationCodePtr = &operationCode;
  operandPtr = &operand;
  accumulatorPtr = &accumulator;
  instructionRegisterPtr = &instructionRegister;

  for ( size_t i = 0; i < MEMSIZE; i++) {
    memory[i] = 0;
  }
FILE *fp;
    char filename[100]="";		//Storing File Path/Name of Image to Display
    printf("\n\nPlease Enter the Full Path of the Image file you want to view: \n");
    scanf("%s",&filename);
    fp=fopen(filename,"r");
    if(fp==NULL){
		printf("\n%s\" File NOT FOUND!",filename);
		exit(1);
	}

  //load program : from file if specified otherwise use manaul entry
  if (argc > 1){
    if(load_file(filename, memory) != 0){
      printf("Error loading your file .\n");
      return 0;
    }else{
      printf("file not found");
    }
  }else{
      load_file(filename, memory);
  }


  //execute program
  execution( accumulatorPtr, instructionCounterPtr, instructionRegisterPtr, operationCodePtr, operandPtr, memory);

  //terminate and printResult : from file on the the screen
  printResult( accumulatorPtr, instructionCounterPtr, instructionRegisterPtr, operationCodePtr, operandPtr, memory);


  return 0;

}