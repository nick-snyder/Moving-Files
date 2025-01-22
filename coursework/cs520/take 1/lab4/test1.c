// simple unit test for symtabCreate, symtabInstall, symtabLookup
// and symtabDelete

#include <stdio.h>

#include "symtab.h"

int main()
{
  void *symtab = symtabCreate(10);
  if (symtab == NULL)
  {
    fprintf(stderr, "symtabCreate failed!\n");
    return -1;
  }
  printf("passed\n");

  if (!symtabInstall(symtab, "MAX", (void *) (long) 42))
  {
    fprintf(stderr, "symtabInstall failed!\n");
    return -1;
  }
  printf("passed\n");

  if (((long) symtabLookup(symtab, "MAX")) != 42)
  {
    fprintf(stderr, "symtabLookup failed!\n");
    return -1;
  }
  printf("passed\n");

  symtabDelete(symtab);

  return 0;
}

