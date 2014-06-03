#include <stdint.h>
#include <stdio.h>

static int i = 0;
static char *message[] = {
  "this ",
  "is ",
  "not ",
  "an ",
  "eight ",
  "part ",
  "message",
  "!!!\n",
};

int main(int argc, char *argv[]){
  uint32_t *p =  (uint32_t *) 0xFFFFFFFF;

  printf("%s", message[i++]);
  if (i < 8) *p = (uint32_t) 1 << i;
  else {
    exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
  }
}

