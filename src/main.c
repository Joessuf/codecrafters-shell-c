#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
while(1) // REPL (Read-Eval-Print Loop) is an interactive loop that forms the core of a shell.
{

  // Flush after every printf

  setbuf(stdout, NULL);

  printf("$ ");

  // Wait for user input

  char input[100];

  fgets(input, 100, stdin); // waits for input , takes 100 char's and listens to the keyboard


  // Remove the trailing newline

  input[strlen(input) - 1] = '\0';


  if(strcmp(input + 5, "exit") == 0) printf("exit is a shell builtin\n");
  else if(strcmp(input + 5, "echo") == 0) printf("echo is a shell builtin\n");
  else if(strcmp(input + 5, "type") == 0) printf("type is a shell builtin\n");

  else
  printf("%s: not found\n", input + 5);

}

  return 0;
}
