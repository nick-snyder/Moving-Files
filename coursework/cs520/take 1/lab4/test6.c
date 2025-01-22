// simple unit test for symtabCreate, symtabInstall, symtabDelete
// with multiple symbol names, and repeating some with different values

#include <stdio.h>
#include <string.h>

#include "symtab.h"

int main()
{
  void *symtab = symtabCreate(8);
  long data = 0;
  if (symtab == NULL)
  {
    fprintf(stderr, "symtabCreate failed!\n");
  }

  if (!symtabInstall(symtab, "MAX", (void *) (long) 42))
  {
    fprintf(stderr, "symtabInstall failed for MAX(1)!\n");
  }

  if (((long) symtabLookup(symtab, "MAXI")) != 44)
  {
    fprintf(stderr, "symtabLookup failed for MAXI!\n");
  }

  if (!symtabInstall(symtab, "MAX", (void *) (long) 92))
  {
    fprintf(stderr, "symtabInstall failed for MAX(2)!\n");
  }
 
   if ((data = (long) symtabLookup(symtab, "MAX")) != 92)
  {
    fprintf(stderr, "symtabLookup failed for MAX(2)!\n");
  }
  else
	fprintf(stderr, "MAX = %ld\n", data);
  
   if (((long) symtabLookup(symtab, "MINI")) == (long) NULL)
  {
    fprintf(stderr, "symtabLookup failed for MINI!\n");
  }
  
  if (!symtabInstall(symtab, "PLUTO", (void *) (long) 32))
  {
    fprintf(stderr, "symtabInstall failed for PLUTO!\n");
  }
  
  if (!symtabInstall(symtab, "DONALD", (void *) (long) -33))
  {
    fprintf(stderr, "symtabInstall failed for DONALD!\n");
  }
  
  if (!symtabInstall(symtab, "DAISY", (void *) (long) -55))
  {
    fprintf(stderr, "symtabInstall failed for DAISY!\n");
  }
  
  void *iter = symtabCreateIterator(symtab);
  if (iter == NULL)
  {
    fprintf(stderr, "symtabCreateIterator failed!\n");
  }

  void *ret;
  const char *sym;
  while((sym = symtabNext(iter, &ret)) != NULL) {
	  fprintf(stderr, "Iterator returned %s = %ld\n", sym, (long) ret);
  }

  symtabDeleteIterator(iter);
  symtabDelete(symtab);

  return 0;
}

