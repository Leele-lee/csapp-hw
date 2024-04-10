#include <stdlib.h>
#include <stdio.h>

/*
  Write a function good_echo that reads a line from standard input and writes it to standard output.
  Your implementation should work for an input line of arbitrary length.
  You may use the library function fgets, but you must make sure your function works correctly
  even when the input line requires more space than you have allocated for your buffer.
  Your code should also check for error conditions and return when one is encountered.
*/

void good_echo() {
  char buffer[100];
  while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
    printf("%s", buffer);
  }
}

int main() {
  good_echo();
  return 0;
}
