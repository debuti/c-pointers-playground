#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STYLE_UNDERLINE    "\033[4m"
#define STYLE_NO_UNDERLINE "\033[24m"

#define STYLE_BOLD         "\033[1m"
#define STYLE_NO_BOLD      "\033[22m"


static const char staticConstArray[] = "Im a static constant array";
const char constArray[] = "Im a constant array";
char justArray[] = "Im just a array";

void helloIamAFunction() {
}

int main() {
  printf("Hello there\n");
  printf("Lets start basic, and we will go sentence by sentence, idea by idea.\n");
  printf("Every couple of concepts you have to press <Enter> to continue the execution, right?\n");
  getchar();


  printf("Ok, i think you got it\n");
  printf("First of all lets start talking about your computer.\n");
  printf("It seems like you're executing in a ");
  if ((size_t)-1 > 0xffffffffUL)
    printf("64 (or more)");
  else
    printf("32 (or less)");
  printf(" bit machine.\n");

  pid_t thisProcessPID = getpid();
  printf("This very same process (with PID %d) is layout like this in (its virtual) memory:\n", thisProcessPID);

  char* procMapsPath = calloc(sizeof(char), strlen("/proc//maps") + (sizeof(int) * 4) + 1);
  sprintf(procMapsPath, "/proc/%d/maps", thisProcessPID);

  char line[1024] = {0};
  FILE* stream = fopen(procMapsPath, "r");
  if (!stream)
        return -1;
  while (fgets(line, 1024, stream)) {
	printf("%s",line);
  }
  fclose(stream);
  printf("Cool, isnt it?\n");
  getchar();


  printf("There are several important sections there, try to find them:\n");
  printf(STYLE_BOLD);
  printf("\tCode section: Is the one that has the eXecute permission and is named after the running program. It also holds const defined variables and other constant data\n");
  printf(STYLE_NO_BOLD);
  printf("\t\tThis is why the local function helloIamAFunction has the address %p\n", &helloIamAFunction);
  printf("\t\tThis is why the static constant staticConstArray has the address %p\n", &staticConstArray);
  printf("\t\tThis is why the constant constArray has the address %p\n", &constArray);
  printf("\t\tThis is why the literal \"Hello world\" has the address %p\n", &"Hello world");
  printf(STYLE_BOLD);
  printf("\tConstants section: Is the one that has just the Read permission and is named after the running program\n");
  printf(STYLE_NO_BOLD);
  printf(STYLE_BOLD);
  printf("\tData section: Is the one that has the ReadWrite permission and is named after the running program\n");
  printf(STYLE_NO_BOLD);
  printf("\t\tThis is why the array justArray has the address %p\n", &justArray);
  printf(STYLE_BOLD);
  printf("\tHeap: This is where the dynamic memory will live\n");
  printf(STYLE_NO_BOLD);
  printf("\t\tThis is why the dynamically allocated procMapsPath is at %p. By the way, I should free it now\n", procMapsPath);
  free(procMapsPath);
  printf(STYLE_BOLD);
  printf("\tStack: This is where the function data and parameters lives\n");
  printf(STYLE_NO_BOLD);
  printf("\t\tThis is why the local thisProcessPID is at %p.\n", &thisProcessPID);
  printf("\n");

  printf("There are lots of things more, but these are just the basics for you to know\n");
  getchar();


  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
}
