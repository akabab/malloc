#include <stdlib.h>
#include "malloc.h"
int main()
{
  int   i;
  char  *addr;

  i = 0;
  while (i < 1024)
  {
    addr = (char *)malloc(1024);
    addr[0] = 42;
    show_alloc_mem();

    free(addr);
    show_alloc_mem();
    i++;
  }
  return (0);
}