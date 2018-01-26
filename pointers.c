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
    
    printf(ANSI_FG_COLOR_YELLOW);
    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
            printf("0x%06x: ", (size_t)mem + i);
        
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
    printf(ANSI_COLOR_RESET);
}
 
void printMemMap(pid_t thisProcessPID) {
  printf(ANSI_FG_COLOR_YELLOW);
  
  char* procMapsPath = calloc(sizeof(char), strlen("/proc//maps") + (sizeof(int) * 4) + 1);
  sprintf(procMapsPath, "/proc/"ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET"/maps", thisProcessPID);

  char line[1024] = {0};
  FILE* stream = fopen(procMapsPath, "r");
  if (stream) {
    while (fgets(line, 1024, stream)) {
            printf("%s",line);
    }
    fclose(stream);
  }
  
  free(procMapsPath);
  
  printf(ANSI_COLOR_RESET);
}

int main() {
  printf("Hello there\n");
  printf("Lets start basic, and we will go sentence by sentence, idea by idea.\n");
  printf("Every couple of concepts you have to press <Enter> to continue the execution, right?\n");
  getchar();


  printf("Ok, i think you got it\n");
  printf("First of all lets start talking about your computer, it seems like you're executing in a ");  
  printf(ANSI_FG_COLOR_GREEN);
  if ((size_t)-1 > 0xffffffffUL)
    printf("64 (or more)");
  else
    printf("32 (or less)");
  printf(ANSI_COLOR_RESET);
  printf(" bit machine.\n");

  pid_t thisProcessPID = getpid();
  printf("This very same process (with PID "ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET") is laid out like this in (its virtual) memory:\n", thisProcessPID);
  printMemMap(thisProcessPID);
  printf("Cool, isnt it?\n");
  getchar();

  char* helloWorldDyn = calloc(sizeof(char), strlen("Hello World") + 1);
  sprintf(helloWorldDyn, "Hello World");

  printf("There are several important sections there, try to find them:\n");
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* A bunch of 0's: From 0x000.. to the first significant segment\n");
  printf(ANSI_COLOR_RESET);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* Program Code or .text: Is the one that has the eXecute permission and is named after the running program. It holds the binary image of the code and also the const defined variables and other constant data\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the local function helloIamAFunction has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &helloIamAFunction);
  printf("\t\tThis is why the static constant staticConstArray has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &staticConstArray);
  printf("\t\tThis is why the constant constArray has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &constArray);
  printf("\t\tThis is why the literal \"Hello world\" has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &"Hello world");
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* Initialised Data or .data: Is the one that has just the Read permission and is named after the running program. It holds initialized static variables\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the static staticInitString has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &staticInitString);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* Uninitialised Data or .bss: Is the one that has the ReadWrite permission and is named after the running program. It holds uninitialized static variables\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the array justArray has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &justArray);
  printf("\t\tThis is why the array staticUninitString has the address "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &staticUninitString);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* Heap: This is where the dynamic memory will live\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the dynamically allocated helloWorldDyn is at "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET". By the way, I should free it now\n", helloWorldDyn);
  printf(ANSI_FG_COLOR_GREEN);
  printf("\t* Stack: This is where the function data and parameters lives\n");
  printf(ANSI_COLOR_RESET);
  printf("\t\tThis is why the local thisProcessPID is at "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET".\n", &thisProcessPID);
  printf("\n");
  printf("There are lots of things more, but these are just the basics for you to know. If you want to learn more about memory layout, see README.md\n");
  getchar();


  printf("Ok, so let me show you your system basic types lengths (in bytes). This info is useful for further steps\n");
  printf(ANSI_FG_COLOR_GREEN);
  printf("\tsizeof(char) = %zd\n", sizeof(char));
  printf("\tsizeof(int) = %zd\n", sizeof(int));
  printf("\tsizeof(long) = %zd\n", sizeof(long));
  printf("\tsizeof(float) = %zd\n", sizeof(float));
  printf("\tsizeof(double) = %zd\n", sizeof(double));
  printf("\tsizeof(size_t) = %zd\n", sizeof(size_t));
  printf("\tsizeof(void*) = %zd\n", sizeof(void*));
  printf(ANSI_COLOR_RESET);
  getchar();

  
  // Definition of a pointer and Starting off
  printf("And now, let me introduce you the pointers.\n");
  int *pi;
  printf("This is pi: \t"ANSI_FG_COLOR_GREEN"int *pi;"ANSI_COLOR_RESET"\n");
  printf("Keep in mind, a pointer is just a memory address. Its defined with a type just for the compiler to know how to handle certain operations with the pointer (more on this later) but its purely a memory address\n");
  int i = 100;
  printf("And this is i: \t"ANSI_FG_COLOR_GREEN"int i=100;"ANSI_COLOR_RESET"\n");
  printf("pi is a pointer to int, this means that is a variable that holds a memory address that represents a pointer.\n");
  printf(" * I dont know where pi points to since we didnt assigned a value to it (=initialized), look, now it points to "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", pi);
  printf(" * I wont try to access the memory pointed by pi, is likely that its outside be legal limits, so it will yield a SegFault, and you wont be able to learn anything more from this tutorial\n");
  printf("i is just a integer initialized to "ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET", that one's easy right?\n", i);
  pi = &i;
  printf("We can do this "ANSI_FG_COLOR_GREEN"pi = &i;"ANSI_COLOR_RESET" So now pi is "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", pi);
  getchar();

  
  printf("We just learn that a int is %zd bytes in length, so im little confused, where do pi it points?\n", sizeof(int));
  printf("Let me dump some memory for you, search for %x (hex repr of "ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET")\n", i, i);
  hexdump(((void*)pi)-16, 32);
  printf("You may have heard about the endianess of the CPU arch, or how the data is sorted out in the memory. How is the integer sorted out??. By the way, ");
  int checkEndianess = 1;
  if(*(char *)&checkEndianess == 1) 
      printf("your system is "ANSI_FG_COLOR_GREEN"Little Endian"ANSI_COLOR_RESET". ");
  else
      printf("your system is "ANSI_FG_COLOR_GREEN"Big Endian"ANSI_COLOR_RESET". ");
  printf("Anyway the pointer will always point to the lower address of the variable pointed, ok?\n");
  getchar();
    
  
  // Assignment and pointers, Dereferencing
  printf("Lets talk about operations with pointers\n");
  printf("You may get the memory location of any variable just by using the & (memory-of) operator before it.\n");
  printf("So, in our playground, the memory address of i, &i is "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET", the memory address of pi, &pi is "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &i, &pi);
  printf("You may get the contents of the memory pointed by any pointer using the * (dereference) operator\n");
  printf("So, the memory address pointed by pi, *pi, has a "ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET". Just like we expected\n", *pi);
  printf("This is one of the things that the type in a pointer declaration is for, the compiler knows it should fetch %zd bytes for this int value\n", sizeof(int));
  *pi=50;
  printf("You could even do write operations like "ANSI_FG_COLOR_GREEN"*pi=50;"ANSI_COLOR_RESET" So now *pi (or i) is "ANSI_FG_COLOR_RED"%d"ANSI_COLOR_RESET"\n", *pi);
  printf("What you cant do is assign some data directly to a pointer, like "ANSI_FG_COLOR_GREEN"pi=50;"ANSI_COLOR_RESET" This will shout \"warning: initialization makes pointer from integer without a cast\" at compile time\n");
  getchar();
  
  
  // Pointer arithmetic (or: why 1 == 4)
  printf("Now we are going to review pointer arithmetics\n");
  printf("This next statement looks legal "ANSI_FG_COLOR_GREEN"pi=pi+1;"ANSI_COLOR_RESET" right?\n");
  printf("It is, and the result would be "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", (pi+1));
  printf("But wait a minute, shouldnt it be 0x%lx?!\n",((size_t)pi)+1);
  printf("Nope, we are incrementing this pointer by one times its type size, so since ints sizes %zd in your system, it outputs that result\n", sizeof(int));
  long *pl;
  printf("Just like a pointer to a long would increment %zd, let me introduce you to pl\t"ANSI_FG_COLOR_GREEN"long *pl;"ANSI_COLOR_RESET"\n", sizeof(long));
  printf(ANSI_FG_COLOR_GREEN"pl"ANSI_COLOR_RESET" is "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET" and "ANSI_FG_COLOR_GREEN"pl+1"ANSI_COLOR_RESET " is "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET". Oh so nice :D, everything falls into place\n", pl, (pl+1));
  getchar();
  
  // Interlude: Arrays
  printf("Lets talk about arrays\n");
  char usefulArray[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
  printf("I just declared a new array: "ANSI_FG_COLOR_GREEN"char usefulArray[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};"ANSI_COLOR_RESET" \n");
  printf("You may know that accessing throgh the [] (subscript) operator is very straighforward, so usefulArray[4] is "ANSI_FG_COLOR_RED"%c"ANSI_COLOR_RESET"\n", usefulArray[4]);
  printf("Easy enough. Check this out\n");
  printf("\t&usefulArray : "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", &usefulArray);
  printf("\tusefulArray : "ANSI_FG_COLOR_BLUE"%p"ANSI_COLOR_RESET"\n", usefulArray);
  printf("Weird huh? This is called decaying, so this tells us that, while an array is really a pointer to the first member of it, it dont behaves like a pointer\n");
  printf("Anyway, you can do this.\n");
  printf("\t&usefulArray+0 : "ANSI_FG_COLOR_BLUE"%c"ANSI_COLOR_RESET"\n", ((char *)&usefulArray)+0);
  printf("\t&usefulArray+1 : "ANSI_FG_COLOR_BLUE"%c"ANSI_COLOR_RESET"\n", &usefulArray+1);
  printf("Let me print the mem for you\n");
  hexdump(((void*)usefulArray)-32, 64);
  
  // Indexing
  // Interlude: Structures and unions
  // Multiple indirection
  // Pointers and const
  // Function pointers
  // Strings (and why there is no such thing)
  // Const pointers in functions
  return 0;
}
