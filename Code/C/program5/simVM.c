//
// A virtual memory simulation.
//
// Virtual memory is a sequence of 32-bit words.
//
// Physical memory is a shorter sequence of 32-bit words.
//
// Virtual memory addresses are 32 bits.
//
// Virtual and physical memory is managed in fixed-size pages.
//
// A page table, which is logically in physical memory, maps virtual
// memory addresses to physical memory addresses. Since physical
// memory is smaller than virtual memory, the page table might indicate
// that a particular page is not currently present in physical memory,
// and that it is logically stored on disk.
//
// However this is a simulation, so all memory words are actually stored
// in the memory of this program, and disk is not used. Similarly the page
// table does not actually exist in the simulated physical memory, but
// rather exists only in the data structures of the simulation.
//
// A translation lookaside buffer (TLB) is simulated. The TLB stores
// recent virtual-to-physical address translations.
//
// The following properties of the virtual memory are set when it is
// created:
//   1. size of the virtual memory in pages
//   2. size of the physical memory in pages
//   3. size of a page in words
//   4. number of TLB entries
//   5. page replacement algorithm
//   6. TLB replacement algorithm
//
// The size of the virtual memory must be larger than the size of the
// physical memory.
//
// The size of a page must be a power of two.
//
// The size of the virtual memory times the size of a page must be less
// than or equal to 2^32.
//
// The size of the TLB should be less than or equal to the size of physical
// memory.
//
// The replacement algorithms are either 0 for round-robin replacement or
// 1 for LRU replacement.
//
// A virtual memory system is initialized to have the first K pages
// of virtual memory loaded into physical memory, where K is the
// number of pages in the physical memory. Initially the virtual
// memory system contains arbitrary values (i.e. not necessarily
// zeros).
//
// The TLB is initialized to have the VM to PM mapping for the
// first N pages loaded into physical pages (i.e. starting at physical
// page 0), where N is the number of TLB entries.
//
// The goal of the simulation is to report the number of page misses,
// the number of TLB misses, and the number of disk writes.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "simVM.h"

#define DEBUG 0

#define VM_ROUNDROBIN_REPLACEMENT 0
#define VM_LRU_REPLACEMENT 1

typedef struct PageTableEntry
{
    int virtualAddress;                 // virtual address of page
    int physicalAddress;                // physical address of page; -1 if on disk 
    int dirtyBit;                       // whether physical address has been modified
    int timeStamp;
}
PageTableEntry;

typedef struct PageTable
{
    PageTableEntry **pageTableEntries;  // list of PageTableEntries
    
    int evictAddress;                   // whichever page gets evicted next; used for round robin algorithm
}
PageTable;

typedef struct TLBEntry
{
    int tag;
    int physicalAddress;
    int timeStamp;
}
TLBEntry;

typedef struct TranslationLookasideBuffer
{
    TLBEntry **tlbEntries;

    int evictAddress;
}
TranslationLookasideBuffer;

typedef struct Memory
{
    float *data;                          // array of data that is basically virtual memory

    PageTable *pageTable;

    TranslationLookasideBuffer *tlb;

    int pageFaults;                     // how many times data was read from disk
    int diskWrites;                     // how many times data was written to disk
    int tlbMisses;

    int time;

    unsigned int sizeVM;                // size of the virtual memory in pages
    unsigned int sizePM;                // size of the physical memory in pages
    unsigned int pageSize;              // size of a page in words
    unsigned int sizeTLB;               // number of translation lookaside buffer entries
    char pageReplAlg;                   // page replacement alg.: 0 is Round Robin, 1 is LRU
    char tlbReplAlg;                    // TLB replacement alg.: 0 is Round Robin, 1 is LRU
}
Memory;

// static int time = 0;

static int myPow(int a, int b);

static void accessVM(void *handle, unsigned int address, int readWrite);

static int findPage(void *handle, int virtualPageNumber, int table);

// virtual memory is an array of pages
// a page is an array of data
// a page table is an array of page table entries
// a page table entry is a key value pair of page pointers

// createVM
//
// Create the virtual memory system and return a "handle" for it.
//
// If there is a violation of any of the constraints on the properties
// of the virtual memory system, this function will return NULL.
//
// If this function fails for any other reason (e.g. malloc returns NULL),
// an error message will be printed to stderr and the program will be
// terminated.
//
void *createVM(
    unsigned int sizeVM,   // size of the virtual memory in pages
    unsigned int sizePM,   // size of the physical memory in pages
    unsigned int pageSize, // size of a page in words
    unsigned int sizeTLB,  // number of translation lookaside buffer entries
    char pageReplAlg,      // page replacement alg.: 0 is Round Robin, 1 is LRU
    char tlbReplAlg        // TLB replacement alg.: 0 is Round Robin, 1 is LRU
)
{
    // check for constraint violations
    if ((sizeVM <= sizePM) || 
        (sizeVM <= 0) ||
        ((pageSize == 0) && ((pageSize & (pageSize - 1)) != 0)) || 
        ((sizeVM * pageSize) > pow(2, 32)) ||
        (sizeTLB > sizePM) ||
        (pageReplAlg != 0 && pageReplAlg != 1) ||
        (tlbReplAlg != 0 && tlbReplAlg != 1))
    {
        return 0;
    }    

    #if DEBUG
        printf("%d %d %d %d %d %d\n", sizeVM, sizePM, pageSize, sizeTLB, pageReplAlg, tlbReplAlg);
    #endif

    // create memory
    Memory *memory = malloc(sizeof(Memory));
    if (memory == NULL)
    {
        return 0;
    }
    memory->data = calloc(sizeof(int), sizeVM * pageSize);
    memory->pageFaults = 0;
    memory->diskWrites = 0;
    memory->tlbMisses = 0;
    memory->time = 0;
    memory->sizeVM = sizeVM;
    memory->sizePM = sizePM;
    memory->pageSize = pageSize;
    memory->sizeTLB = sizeTLB;
    memory->pageReplAlg = pageReplAlg;
    memory->tlbReplAlg = tlbReplAlg;

    // create page table
    PageTable *pageTable = malloc(sizeof *pageTable);
    if (pageTable == NULL)
    {
        return 0;
    }
    pageTable->evictAddress = 0;
    pageTable->pageTableEntries = calloc(sizeof(PageTableEntry*), sizePM);

    // create a page table entry for each page in physical memory
    for (int i = 0; i < sizePM; i++)
    {
        // allocate page table entries
        pageTable->pageTableEntries[i] = malloc(sizeof(PageTableEntry));
        if (pageTable->pageTableEntries[i] == NULL)
        {
            return 0;
        }
        pageTable->pageTableEntries[i]->virtualAddress = i; 
        pageTable->pageTableEntries[i]->physicalAddress = i; 
        pageTable->pageTableEntries[i]->dirtyBit = 0;
        pageTable->pageTableEntries[i]->timeStamp = 0;
    }
    memory->pageTable = pageTable;

    TranslationLookasideBuffer *tlb = malloc(sizeof *tlb);
    if (tlb == NULL)
    {
        return 0;
    }
    tlb->evictAddress = 0;
    tlb->tlbEntries = calloc(sizeof(TLBEntry*), sizeTLB);
    for (int i = 0; i < sizeTLB; i++)
    {
        // allocate TLB entries
        tlb->tlbEntries[i] = malloc(sizeof(TLBEntry));
        if (tlb->tlbEntries[i] == NULL)
        {
            return 0;
        }
        tlb->tlbEntries[i]->tag = i;
        tlb->tlbEntries[i]->physicalAddress = i;
        tlb->tlbEntries[i]->timeStamp = 0;
    }
    memory->tlb = tlb;
    
    // return handle
    return memory;
}

// readInt
//
// Read an int from virtual memory.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
// If the address is out of range, an error message will be printed to
// stderr and the program will be terminated.
//
int readInt(void *handle, unsigned int address)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "readInt failed!\n");
        exit(-1);
    }

    accessVM(handle, address, 1);

    return (int) memory->data[address];
}

// readFloat
//
// Read a float from virtual memory.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
// If the address is out of range, an error message will be printed to
// stderr and the program will be terminated.
//
float readFloat(void *handle, unsigned int address)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "readFloat failed!\n");
        exit(-1);
    }

    accessVM(handle, address, 1);

    return (float) memory->data[address];
}

// writeInt
//
// Write an int to virtual memory.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
// If the address is out of range, an error message will be printed to
// stderr and the program will be terminated.
//
void writeInt(void *handle, unsigned int address, int value)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "writeInt failed!\n");
        exit(-1);
    }

    accessVM(handle, address, 0);

    memory->data[address] = value;
}

// writeFloat
//
// Write a float to virtual memory.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
// If the address is out of range, an error message will be printed to
// stderr and the program will be terminated.
//
void writeFloat(void *handle, unsigned int address, float value)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "writeFloat failed!\n");
        exit(-1);
    }

    accessVM(memory, address, 0);

    memory->data[address] = value;
}

// printStatistics
//
// Print the total number of page faults, the total number of TLB misses
// and the total number of disk writes.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
// Here is a sample output:
//
//   Number of page faults: 123
//   Number of TLB misses: 125
//   Number of disk writes: 64
//
void printStatistics(void *handle)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        return;
    }

    printf("Number of page faults: %d\n", memory->pageFaults);

    printf("Number of TLB misses: %d\n", memory->tlbMisses);

    printf("Number of disk writes: %d\n", memory->diskWrites);

    #if DEBUG

        printf("\ntlb:\n");
        // int a = 0;
        for (int b = 0; b < memory->sizeTLB; b++)
        {
            TLBEntry *tlbe = memory->tlb->tlbEntries[b];
            printf("TLBE: %d %d %d\n", tlbe->tag, tlbe->physicalAddress, tlbe->timeStamp);
        }

        printf("\npage table:\n");
        int k = 0;
        for (int i = 0; i < memory->sizePM; i++)
        {
            PageTableEntry *pte = memory->pageTable->pageTableEntries[i];
            printf("PTE: %d %d %d %d\n", pte->virtualAddress, pte->physicalAddress, pte->dirtyBit, pte->timeStamp);
            for (int j = 0; j < memory->pageSize; j++)
            {
                printf("  [%d]: %d\n", j, memory->data[k]);
                k++;
            }
        } 
    #endif
}

// cleanupVM
//
// Cleanup the memory used by the simulation of the virtual memory system.
//
// If the handle is not one returned by createVM, the behavior is
// undefined.
//
void cleanupVM(void *handle)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        return;
    }

    for (int i = 0; i < memory->sizePM; i++)
    {
        free(memory->pageTable->pageTableEntries[i]);
    }
    free(memory->pageTable->pageTableEntries);
    free(memory->pageTable);

    for (int i = 0; i < memory->sizeTLB; i++)
    {
        free(memory->tlb->tlbEntries[i]);
    }
    free(memory->tlb->tlbEntries);
    free(memory->tlb);
    
    free(memory->data);

    free(memory);
}

static int myPow(int a, int b)
{
    int ret = 1;
    for (int i = 0; i < b; i++)
    {
        ret = ret * a;
    }

    return ret;
}

static void accessVM(void *handle, unsigned int address, int readWrite)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "accessVM failed!\n");
        exit(-1);
    }

    if (address > memory->sizeVM * memory->pageSize) 
    {
        fprintf(stderr, "Address, %d, is too large for size %d", address, memory->sizeVM * memory->pageSize);
        exit(-1);
    }

    unsigned int virtualPageNumber;
    unsigned int offsetValue;

    for (int i = 0; i < 32; i++)
    {
        if (myPow(2, i) == memory->pageSize)
        {
            offsetValue = address & (memory->pageSize - 1);

            virtualPageNumber = address >> i;

            break;
        }
    }

    // look for page in the TLB
    int pageIndexTLB = findPage(memory, virtualPageNumber, 0);
    if (pageIndexTLB != -1)
    {
        // find the page from the TLB in the page table and mark it dirty
        for (int j = 0; j < memory->sizePM; j++)
        {
            if (memory->pageTable->pageTableEntries[j]->virtualAddress == virtualPageNumber)
            {
                memory->pageTable->pageTableEntries[j]->dirtyBit = 1;
            }
        }

        // update time when TLB entry was visited
        memory->tlb->tlbEntries[pageIndexTLB]->timeStamp = memory->time;
        memory->time++;
    }
    else
    {   
        memory->tlbMisses++;

        // look for the page in the page table
        int pageIndexPT = findPage(memory, virtualPageNumber, 1);
        if (pageIndexPT != -1)
        {
            // the page was found in the page table               
            // mark the page dirty and update the time stamp
            memory->pageTable->pageTableEntries[pageIndexPT]->dirtyBit = 1;
            memory->pageTable->pageTableEntries[pageIndexPT]->timeStamp = memory->time;
            memory->time++;

            // copy the page over to the TLB
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->tag = virtualPageNumber;
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->physicalAddress = memory->pageTable->pageTableEntries[pageIndexPT]->physicalAddress;
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->timeStamp = memory->time;
            memory->time++;

            // update next TLB evict address
            if (memory->tlbReplAlg == 0)
            {
                // round robin

                // move next evict address
                memory->tlb->evictAddress = (memory->tlb->evictAddress + 1) % memory->sizeTLB;
            }
            else
            {
                // LRU

                // find lowest time stamp
                int newLow = 0;
                int oldLow = 1;
                for (int i = 0; i < memory->sizeTLB; i++)
                {
                    newLow = memory->tlb->tlbEntries[i]->timeStamp;
                    if (newLow < oldLow)
                    {
                        oldLow = memory->tlb->tlbEntries[i]->timeStamp;
                        memory->tlb->evictAddress = memory->tlb->tlbEntries[i]->tag;
                    }
                }
            }
        }
        else
        {
            // the page is not in TLB and not in the page table, worst case

            #if DEBUG
                printf("\nvirtual page leads to the disk\n");
                printf("page #%d will be evicted to disk and page #%d will take its place in physical memory\n", memory->pageTable->evictAddress, virtualPageNumber);
            #endif

            if (readWrite == 1)
            {
                // incure a disk write if the evicted page is dirty
                if (memory->pageTable->pageTableEntries[memory->pageTable->evictAddress]->dirtyBit == 1)
                {
                    // incur a disk write
                    memory->diskWrites++;
                }
            }
            
            // incur a page fault because the new page is on disk
            memory->pageFaults++;

            // replace the evicted page with the new page
            memory->pageTable->pageTableEntries[memory->pageTable->evictAddress]->virtualAddress = virtualPageNumber;
            memory->pageTable->pageTableEntries[memory->pageTable->evictAddress]->dirtyBit = 1;
            memory->pageTable->pageTableEntries[memory->pageTable->evictAddress]->timeStamp = memory->time;
            memory->time++;

            // copy over data from the page table to the new page to the TLB
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->tag = virtualPageNumber;
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->physicalAddress = memory->pageTable->pageTableEntries[memory->pageTable->evictAddress]->physicalAddress;
            memory->tlb->tlbEntries[memory->tlb->evictAddress]->timeStamp = memory->time;
            memory->time++;

            // choose the replacement algorithm
            if (memory->pageReplAlg == 0)
            {
                // round robin

                // move to the next evict address
                memory->pageTable->evictAddress = (memory->pageTable->evictAddress + 1) % memory->pageSize;
            }
            else
            {
                // LRU

                // find lowest time stamp
                int newLow = 0;
                int oldLow = 1;
                for (int i = 0; i < memory->sizePM; i++)
                {
                    newLow = memory->pageTable->pageTableEntries[i]->timeStamp;
                    if (newLow < oldLow)
                    {
                        oldLow = memory->pageTable->pageTableEntries[i]->timeStamp;
                        memory->pageTable->evictAddress = memory->pageTable->pageTableEntries[i]->virtualAddress;
                    }
                }
            }

            // add to TLB by evicting another TLB entry
            if (memory->tlbReplAlg == 0)
            {
                // round robin

                // move next evict address
                memory->tlb->evictAddress = (memory->tlb->evictAddress + 1) % memory->sizeTLB;
            }
            else
            {
                // LRU

                // find lowest time stamp
                int newLow = 0;
                int oldLow = 1;
                for (int i = 0; i < memory->sizeTLB; i++)
                {
                    newLow = memory->tlb->tlbEntries[i]->timeStamp;
                    if (newLow < oldLow)
                    {
                        oldLow = memory->tlb->tlbEntries[i]->timeStamp;
                        memory->tlb->evictAddress = memory->tlb->tlbEntries[i]->tag;
                    }
                }
            }
        }
    }
}

static int findPage(void *handle, int virtualPageNumber, int table)
{
    Memory *memory = handle;
    if (memory == NULL)
    {
        fprintf(stderr, "findPage failed!\n");
        exit(-1);
    }

    int ret = -1;
    
    if (table == 0)
    {
        for (int i = 0; i < memory->sizeTLB; i++)
        {
            if (memory->tlb->tlbEntries[i]->tag == virtualPageNumber)
            {
                ret = i;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < memory->sizePM; i++)
        {
            if (memory->pageTable->pageTableEntries[i]->virtualAddress == virtualPageNumber)
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}