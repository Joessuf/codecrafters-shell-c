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


  if(strcmp(input, "exit") == 0) exit(0); // isnt input here a char how did we compare it to a string ??

  else if (strncmp(input, "echo", 3) == 0) printf("%s\n", input + 5);

  else if (strncmp(input, "type", 3) == 0)
  {
      if(strcmp(input + 5, "type") == 0) printf("%s is a shell builtin\n", input + 3);
      else if(strcmp(input + 5, "echo") == 0) printf("%s is a shell builtin\n", input + 3);
      else if(strcmp(input + 5, "exit") == 0) printf("%s is a shell builtin\n", input + 3);
      else printf("%s: not found", input);
  }

  else
  printf("%s: command not found\n", input);

}

  return 0;
}
