#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

  while (1) {

    setbuf(stdout, NULL);

    printf("$ ");

    char input[100];

    fgets(input, 100, stdin);

    input[strlen(input) - 1] = '\0';

    if (strcmp(input, "exit") == 0)

      exit(0);

    else if (strncmp(input, "echo", 4) == 0)

      printf("%s\n", input + 5);

    else if (strncmp(input, "type", 4) == 0) {

      if (strcmp(input + 5, "type") == 0)

        printf("%s is a shell builtin\n", input + 5);

      else if (strcmp(input + 5, "echo") == 0)

        printf("%s is a shell builtin\n", input + 5);

      else if (strcmp(input + 5, "exit") == 0)

        printf("%s is a shell builtin\n", input + 5);

      else {

        char *path_env = getenv("PATH");

        char *path_copy = strdup(path_env);

        char *dir = strtok(path_copy, ":");

        int found = 0;

        while (dir != NULL && !found) {

          char full_path[1024];

          snprintf(full_path, sizeof(full_path), "%s/%s", dir, input + 5);

          if (access(full_path, X_OK) == 0) {

            printf("%s is %s\n", input + 5, full_path);

            found = 1;

            break;

          }

          dir = strtok(NULL, ":");

        }

        free(path_copy);

        if (!found) {

          printf("%s: not found\n", input + 5);

        }

      }

    }

    else {

      char *path_env = getenv("PATH");

      if (path_env == NULL) {

        printf("%s: command not found\n", input);

      } else {

        char input_copy[100];

        strcpy(input_copy, input);

        int argc = 0;

        char *args[20];

        char *token = strtok(input_copy, " ");

        while (token != NULL && argc < 19) {

          args[argc] = token;

          argc++;

          token = strtok(NULL, " ");

        }

        args[argc] = NULL;

        char *path_copy = strdup(path_env);

        char *dir = strtok(path_copy, ":");

        int found = 0;

        while (dir != NULL && !found) {

          char full_path[1024];

          snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);

          if (access(full_path, F_OK) == 0) {

            found = 1;

            break;

          }

          dir = strtok(NULL, ":");

        }

        free(path_copy);

        if (found) {

          pid_t pid = fork();

          if (pid == 0) {

            execvp(args[0], args);

            exit(1);

          } else if (pid > 0) {

            int status;

            waitpid(pid, &status, 0);

          }

        } else {

          printf("%s: command not found\n", args[0]);

        }

      }

    }

  }

  return 0;

}
