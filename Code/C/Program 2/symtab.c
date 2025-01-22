//
// This is the interface for a generic symbol table. A table stores
// (symbol, data) pairs.
//
// A symbol is simply a C string (null-terminated char sequence).
//
// The data associated with a symbol is simply a void*.
//

#include <stdlib.h>
#include <string.h>
#include "symtab.h"

// Define a struct to be linked together at one level of the hash table. 
// This struct needs to have a char* member for the symbol, a void* member 
// for the data pointer, and a member to point to the next struct in the 
// linked list. I recommend using a typedef to define a name for the struct 
// type.
typedef struct 
{
    char* symbol;
    void* data;
    struct Node* next;
} 
Node;

// Define a struct to hold the control information for one symbol table. 
// This struct needs to have a member to hold the length of the hash 
// table and a member to point to the array of that length that contains 
// pointers to the structs that are linked together. This latter member 
// is a bit tricky, as it is a pointer to a pointer to the linked struct. 
// Again I recommend using a typedef to define a name for the struct type
typedef struct 
{
    int length;
    Node** array;
} 
Table;

// modified FNV hash (see http://en.wikipedia.org/wiki/Fowler_Noll_Vo_hash)
static unsigned int hash(const char *str)
{
    const unsigned int p = 16777619;
    unsigned int hash = 2166136261u;

    while (*str)
    {
        hash = (hash ^ *str) * p;
        str += 1;
    }

    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;

    return hash;
}
    // Implement a helper function to do an internal lookup of a symbol in a 
    // given table, returning a pointer to the linked struct containing the 
    // symbol, if one is found. The function should be passed the control 
    // struct for a hash table and a const char* pointer to the symbol. (The 
    // const keyword indicates that the function should not change the 
    // characters in the string representing the symbol.) The function should 
    // use the hash function to "hash" the symbol to an integer value and then
    // compute the modulus of that integer and the table's length. The symbol 
    // is then searched for on the linked list at that level in the table. Use 
    // the strcmp function to compare symbol strings. (Be careful, strcmp 
    // returns zero when the strings are identical.) If the symbol is found, 
    // then return a pointer to the struct that contains the symbol. If the 
    // symbol is not found, then return NULL.

    // Use the static keyword to indicate that both the hash function and the 
    // lookup helper function should not be called from outside this file. 
    // (That is, they are not part of the public interface of this file.) 
static Node *internalLookup(Table table, const char* symbol)
{
    // hash the symbol to an integer
    int symInt = hash(symbol);

    // compute the modulus of that integer and the table's length
    symInt = symInt % table.length;

    // The symbol is then searched for on the linked list at that level in the table
    Node *node = symtabHandle(symInt);
    while (node != NULL)
    {
        node = node->next;
    
    // Use the strcmp function to compare symbol strings. (Be careful, strcmp returns zero when the strings are identical.)
        if (strcmp(symbol, node->symbol) == 0)
        {
    // If the symbol is found, then return a pointer to the struct that contains the symbol.
            return node;

    // If the symbol is not found, then return NULL.
        }
        else
        {
            return NULL;
        }
    }
    return node;
}

void *symtabCreate(int sizeHint)
{
    // Use malloc to allocate space for a control struct for the new symbol table. Use sizeof with
    // the typedef name for the control struct to calculate the size in bytes of the struct, which is
    // the value that should be passed to malloc
    Table *table = (Table *) malloc(sizeof(Table));

    // Check the return value of malloc and, if NULL, return NULL. 
    if (table == NULL)
    {
        return NULL;
    }

    // Initialize the length member of the new member with the sizeHint value passed in to symtabCreate.
    table->length = sizeHint;

    // Use malloc to allocate a array of pointers to the linked struct. The size in bytes of this
    // array is computed by multiplying the size of a pointer to a linked struct times the length
    // member. Store the returned pointer in the second member of the control struct.
    table->array = (Table**) malloc((sizeof(Node)) * table->length);

    // Check the return value of malloc and, if NULL, call free to deallocate memory for the
    // control struct and then return NULL. 
    if (table->array == NULL)
    {
        free(table);
        return NULL;
    }

    // Return a pointer to the control struct.
    return table;
}
  // Creates a symbol table.
  // If successful, returns a handle for the new table.
  // If memory cannot be allocated for the table, returns NULL.
  // The parameter is a hint as to the expected number of (symbol, data)
  //   pairs to be stored in the table.

void symtabDelete(void *symtabHandle)
{
    Node *delNode = symtabHandle->array[0];
    if (delNode->next)
    {
        Node *curNode = delNode->next;

        while ((symtabHandle->length > 0) && delNode)
        {
            free(delNode);
            if (curNode)
            {
                curNode = curNode->next;
            }
        }
    }
    else
    {
        free(delNode);
    }
}
  // Deletes a symbol table.
  // Reclaims all memory used by the table.
  // Note that the memory associate with data items is not reclaimed since
  //   the symbol table does not know the actual type of the data. It only
  //   manipulates pointers to the data.
  // Also note that no validation is made of the symbol table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).

int symtabInstall(void *symtabHandle, const char *symbol, void *data)
{
    // Call the lookup helper function to check if the symbol is already in the table.
    Node* node = internalLookup(*symtabHandle, symbol);

    // If the symbol is found in the table, then simply update the data member of the struct returned by the lookup helper function.
    if (node == NULL)
    {
        node->data = data;
    }  

    // If the symbol is not found, then use malloc to allocate a new linked struct
    else
    {
        Node *newNode = (Node *) malloc(sizeof(Node));
        if (newNode == NULL)
        {
            return 0;
        }

        // Also use malloc to allocate space for a copy of the new symbol
        char *copySymbol = (char *) malloc(sizeof(char) + 1);
        if (copySymbol == NULL)
        {
            return 0;
        }

        // Use strlen to compute the length of the string representing the symbol
        // (When calling malloc don't forget to add one for the NULL byte on the end of C strings
        int symbolLength = strlen(copySymbol);
        // strlen does not count this NULL byte but you need to allocate space for it.


        // Use strcpy to copy the symbol string to the newly allocated space
        strcpy(newNode->symbol, copySymbol);

        // Store a pointer to the copy of the symbol in the symbol member of the new linked struct
        newNode->symbol = *copySymbol;
        
        // Store the data value in the data member of the struct
        newNode->data = data;

        // Use the hash function applied to the symbol modulus the table length to 
        // compute the level in the table where the new linked struct should be inserted
        // It is probably easiest to link the new struct on the front of this list
        int level = hash(symbol % symtabHandle->length);

    }

    // If a call to malloc fails, then return 0; otherwise return 1
    return 1;
}
  // Install a (symbol, data) pair in the table.
  // If the symbol is already installed in the table, then the data is
  //   overwritten.
  // If the symbol is not already installed, then space is allocated and
  //   a copy is made of the symbol, and the (symbol, data) pair is then
  //   installed in the table.
  // If successful, returns 1.
  // If memory cannot be allocated for a new symbol, then returns 0.
  // Note that no validation is made of the symbol table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).

void *symtabLookup(void *symtabHandle, const char *symbol)
{
    Node *node = internalLookup(*symtabHandle, symbol);
    if (node)
    {
        return node->data;
    }
    else 
    {
        return NULL;
    }
}
  // Return the data item stored with the given symbol.
  // If the symbol is found, return the associated data item.
  // If the symbol is not found, returns NULL.
  // Note that no validation is made of the symbol table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).

void *symtabCreateIterator(void *symtabHandle)
{
    return 0;
}
  // Create an iterator for the contents of the symbol table.
  // If successful, a handle to the iterator is returned which can be
  // repeatedly passed to symtabNext to iterate over the contents
  // of the table.
  // If memory cannot be allocated for the iterator, returns NULL.
  // Note that no validation is made of the symbol table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).

const char *symtabNext(void *iteratorHandle, void **returnData)
{
    return 0;
}
  // Returns the next (symbol, data) pair for the iterator.
  // The symbol is returned as the return value and the data item
  // is placed in the location indicated by the second parameter.
  // If the whole table has already been traversed then NULL is
  //   returned and the location indicated by the second paramter
  //   is not modified.
  // Note that no validation is made of the iterator table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).
  // Also note that if there has been a symbtabInstall call since the
  //   iterator was created, the behavior is undefined (but probably
  //   benign).

void symtabDeleteIterator(void *iteratorHandle)
{
    //return 0;
}
  // Delete the iterator indicated by the only parameter.
  // Reclaims all memory used by the iterator.
  // Note that no validation is made of the iterator table handle passed
  //   in. If not a valid handle, then the behavior is undefined (but
  //   probably bad).

