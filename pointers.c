#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
 
#define ANSI_BOLD                          "\x1B[1m"
#define ANSI_UNDERLINE                     "\x1B[4m"
#define ANSI_SLOWBLINK                     "\x1B[5m"
#define ANSI_FG_COLOR_RED                  "\x1B[31m"
#define ANSI_FG_COLOR_BRIGHTRED            "\x1B[91m"
#define ANSI_FG_COLOR_GREEN                "\x1B[32m"
#define ANSI_FG_COLOR_BRIGHTGREEN          "\x1B[92m"
#define ANSI_FG_COLOR_YELLOW               "\x1B[33m"
#define ANSI_FG_COLOR_BRIGHTYELLOW         "\x1B[93m"
#define ANSI_FG_COLOR_BLUE                 "\x1B[34m"
#define ANSI_FG_COLOR_BRIGHTBLUE           "\x1B[94m"
#define ANSI_FG_COLOR_MAGENTA              "\x1B[35m"
#define ANSI_FG_COLOR_BRIGHTMAGENTA        "\x1B[95m"
#define ANSI_FG_COLOR_CYAN                 "\x1B[36m"
#define ANSI_FG_COLOR_BRIGHTCYAN           "\x1B[96m"
#define ANSI_BG_COLOR_RED                  "\x1B[41m"
#define ANSI_BG_COLOR_BRIGHTRED            "\x1B[101m"
#define ANSI_BG_COLOR_GREEN                "\x1B[42m"
#define ANSI_BG_COLOR_BRIGHTGREEN          "\x1B[102m"
#define ANSI_BG_COLOR_YELLOW               "\x1B[43m"
#define ANSI_BG_COLOR_BRIGHTYELLOW         "\x1B[103m"
#define ANSI_BG_COLOR_BLUE                 "\x1B[44m"
#define ANSI_BG_COLOR_BRIGHTBLUE           "\x1B[104m"
#define ANSI_BG_COLOR_MAGENTA              "\x1B[45m"
#define ANSI_BG_COLOR_BRIGHTMAGENTA        "\x1B[105m"
#define ANSI_BG_COLOR_CYAN                 "\x1B[46m"
#define ANSI_BG_COLOR_BRIGHTCYAN           "\x1B[106m"
#define ANSI_COLOR_RESET                   "\x1B[0m"


#define HEXDUMP_COLS 16


static const char staticConstArray[] = "Im a static constant array";
static char *staticInitString = "Im a static initialized string";
static char *staticUninitString;
const char constArray[] = "Im a constant array";
char justArray[] = "Im just a array";


void helloIamAFunction() {
}

 
void hexdump(void *mem, unsigned int len) {
    unsigned int i, j;
    
    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
            printf("0x%06x: ", i);
        
        /* print hex data */
        if(i < len)
            printf("%02x ", 0xFF & ((char*)mem)[i]);
        else /* end of block, just aligning for ASCII dump */
            printf("   ");
        
        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
                if(j >= len) /* end of block, not really printing */
                    putchar(' ');
                else if(isprint(((char*)mem)[j])) /* printable char */
                    putchar(0xFF & ((char*)mem)[j]);        
                else /* other char */
                    putchar('.');
            putchar('\n');
        }
    }
}
 

int main() {
  printf("Hello there\n");
  printf("Lets start basic, and we will go sentence by sentence, idea by idea.\n");
  printf("Every couple of concepts you have to press <Enter> to continue the execution, right?\n");
  getchar();


  printf("Ok, i think you got it\n");
  printf("First of all lets start talking about your computer.\n");
  printf("It seems like you're executing in a ");  
  printf(ANSI_FG_COLOR_GREEN);
  if ((size_t)-1 > 0xffffffffUL)
    printf("64 (or more)");
  else
    printf("32 (or less)");
  printf(ANSI_COLOR_RESET);
  printf(" bit machine.\n");

  pid_t thisProcessPID = getpid();
  printf("This very same process (with PID %d) is laid out like this in (its virtual) memory:\n", thisProcessPID);

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
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tProgram Code or .text: Is the one that has the eXecute permission and is named after the running program. It holds the binary image of the code and also holds const defined variables and other constant data\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the local function helloIamAFunction has the address %p\n", &helloIamAFunction);
  printf("\t\tThis is why the static constant staticConstArray has the address %p\n", &staticConstArray);
  printf("\t\tThis is why the constant constArray has the address %p\n", &constArray);
  printf("\t\tThis is why the literal \"Hello world\" has the address %p\n", &"Hello world");
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tInitialised Data or .data: Is the one that has just the Read permission and is named after the running program. It holds initialized static variables\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the static staticInitString has the address %p\n", &staticInitString);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tUninitialised Data or .bss: Is the one that has the ReadWrite permission and is named after the running program. It holds uninitialized static variables\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the array justArray has the address %p\n", &justArray);
  printf("\t\tThis is why the array staticUninitString has the address %p\n", &staticUninitString);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tHeap: This is where the dynamic memory will live\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the dynamically allocated procMapsPath is at %p. By the way, I should free it now\n", procMapsPath);
  free(procMapsPath);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tStack: This is where the function data and parameters lives\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the local thisProcessPID is at %p.\n", &thisProcessPID);
  printf("\n");
  printf("There are lots of things more, but these are just the basics for you to know. If you want to learn more about memory layout, see README.md\n");
  getchar();


  printf("Ok, so let me show you your system basic types lengths (in bytes). This info is useful for further steps\n");
  printf("\tsizeof(char) = %zd\n", sizeof(char));
  printf("\tsizeof(int) = %zd\n", sizeof(int));
  printf("\tsizeof(long) = %zd\n", sizeof(long));
  printf("\tsizeof(float) = %zd\n", sizeof(float));
  printf("\tsizeof(double) = %zd\n", sizeof(double));
  printf("\tsizeof(size_t) = %zd\n", sizeof(size_t));
  printf("\tsizeof(void*) = %zd\n", sizeof(void*));
  getchar();

  
  // Definition of a pointer and Starting off
  printf("And now, let me introduce you the pointers.\n");
  int *pi;
  printf("This is pi: \t"ANSI_FG_COLOR_GREEN"int *pi;"ANSI_COLOR_RESET"\n");
  printf("Keep in mind, a pointer is just a memory address. Its defined with a type just for the compiler to know how to handle certain operations with the pointer, more on this later\n");
  int i = 100;
  printf("And this is i: \t"ANSI_FG_COLOR_GREEN"int i=100;"ANSI_COLOR_RESET"\n");
  printf("pi is a pointer to int, this means that is a variable that holds a memory address that represents a pointer.\n");
  printf(" * I dont know where pi points to since we didnt assigned a value to it, look, now it points to %p\n", pi);
  printf(" * I wont try to access the memory pointed by pi, is likely that its outside be legal limits, so it will yield a SegFault, and you wont be able to learn anything more from this tutorial\n");
  printf("i is just a integer initialized to %d, that one's easy right?\n", i);
  pi = &i;
  printf("We can do this "ANSI_FG_COLOR_GREEN"pi = &i;"ANSI_COLOR_RESET" So now pi is %p\n", pi);
  printf("\n");
  printf("We just learn that a int is %zd bytes in length, so im little confused, where do pi it points?\n", sizeof(int));
  printf("Let me dump some memory for you, search for %x (hex repr of %d)\n", i, i);
  hexdump(((void*)pi)-16, 32);
  printf("You may have heard about the endianess of the CPU arch, or how the data is sorted out in the memory. How is the integer sorted out??. By the way, ");
  int checkEndianess = 1;
  if(*(char *)&checkEndianess == 1) 
      printf("your system is "ANSI_FG_COLOR_GREEN"Little Endian"ANSI_COLOR_RESET"\n");
  else
      printf("your system is "ANSI_FG_COLOR_GREEN"Big Endian"ANSI_COLOR_RESET"\n");
  printf("Anyway the pointer will always point to the lower address of the variable pointed, ok?\n");
  getchar();
    
  
  // Assignment and pointers, Dereferencing
  printf("Lets talk about operations with pointers\n");
  printf("You may get the memory location of any variable just by using the & (memory-of) operator before it.\n");
  printf("So, in our playground, the memory address of i, &i is %p, the memory address of pi, &pi is %p\n", &i, &pi);
  printf("You may get the contents of the memory pointed by any pointer using the * (dereference) operator\n");
  printf("So, the memory address pointed by pi, *pi has a %d. Just like we expected\n", *pi);
  printf("This is one of the things that the type in a pointer def is for, the compiler knows it should fetch %zd bytes for this int value\n", sizeof(int));
  *pi=50;
  printf("You could even do write operations like "ANSI_FG_COLOR_GREEN"*pi=50;"ANSI_COLOR_RESET" So now *pi (or i) is %d\n", *pi);
  printf("What you cant do is assign some data directly to a pointer, like "ANSI_FG_COLOR_GREEN"pi=50;"ANSI_COLOR_RESET" This will shout \"warning: initialization makes pointer from integer without a cast\" at compile time\n");
  getchar();
  
  
  // Interlude: Arrays
  // Pointer arithmetic (or: why 1 == 4)
  printf("Now we are going to review pointer arithmetics\n");
  printf("This next statement looks legal "ANSI_FG_COLOR_GREEN"pi=pi+1;"ANSI_COLOR_RESET" right?\n");
  printf("It is, and the result would be %p\n", (pi+1));
  printf("But wait a minute, shouldnt it be 0x%lx?!\n",((size_t)pi)+1);
  printf("Nope, we are incrementing this pointer by one times its type size, so since ints sizes %zd in your system, it outputs that result\n", sizeof(int));
  long *pl;
  printf("Just like a pointer to a long would increment %zd, let me introduce you to pl\t"ANSI_FG_COLOR_GREEN"long *pl;"ANSI_COLOR_RESET"\n", sizeof(long));
  printf(ANSI_FG_COLOR_GREEN"pl"ANSI_COLOR_RESET" is %p and "ANSI_FG_COLOR_GREEN"pl+1"ANSI_COLOR_RESET " is %p. Oh so nice :D, everything falls into place\n", pl, (pl+1));
  
  
  // Indexing
  // Interlude: Structures and unions
  // Multiple indirection
  // Pointers and const
  // Function pointers
  // Strings (and why there is no such thing)
  // Const pointers in functions
  return 0;
}
