#include <stdio.h>

int main(int argc, char *argv[]){
  printf("Hi from processor MIPS!\n");

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

