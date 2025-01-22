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

#define DEBUG 1

#define VM_ROUNDROBIN_REPLACEMENT 0
#define VM_LRU_REPLACEMENT 1

typedef struct PageTableEntry
{
    int virtAddress;                // virtual address of page
    int physAddress;                // physical address of page; -1 if on disk 
    int dirty;                      // whether physical address has been modified
    int timeStamp;
}
PageTableEntry;

typedef struct PageTable
{
    PageTableEntry **pageTableEntries;
    int pageFaults;                 // how many times data was read from disk
    int diskWrites;                 // how many times data was written to disk
    unsigned int nextAddress;       // whichever page gets evicted next; used for round robin algorithm
    int time;                       // time in page table; used for LRU algorithm
}
PageTable;

typedef struct Offset                                                                                             // fix
{
    void *value;                    // int/float
    int residentOffset;             // Data's personal offset in a page
}
Offset;

typedef struct Page                                                                                             // fix
{
    Offset **offset;                    // array of Data for each offset
    unsigned int residentAddress;   // index in PhysicalMemory
    int pageSize;                       // size of page ???
}
Page;

typedef struct VirtualMemory
{
    Page **pages;                    // array of pages that simulates physical memory; made up of pages
    unsigned int sizeVM;
}
VirtualMemory;

typedef struct PhysicalMemory
{
    Page **pages;                    // array of pages that simulates physical memory; made up of pages
    unsigned int sizePM;
}
PhysicalMemory;

typedef struct Simulation
{
    VirtualMemory *virtualMemory;
    PageTable *pageTable;
    PhysicalMemory *physicalMemory;
}
Simulation;


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
    if (!(sizeVM > sizePM) || 
        !((pageSize != 0) && ((pageSize & (pageSize - 1)) == 0)) || 
        !((sizeVM * pageSize) < pow(2, 32)) ||
        !(sizeTLB <= sizePM) ||
        !((pageReplAlg >= 0) && (pageReplAlg <= 1)) ||
        !((tlbReplAlg >= 0) && (tlbReplAlg <= 1)))
    {
        return NULL;
    }    

    #if DEBUG
        printf("%d %d %d %d %d %d\n", sizeVM, sizePM, pageSize, sizeTLB, pageReplAlg, tlbReplAlg);
    #endif

    // create simulation
    Simulation *simulation = malloc(sizeof(Simulation));
    

    // create virtual memory
    simulation->virtualMemory = malloc(sizeof(VirtualMemory));
    simulation->virtualMemory->pages = malloc(sizeof(Page*));
    simulation->virtualMemory->sizeVM = sizeVM;

    // for each page in virtual memory
    for (int i = 0; i < sizeVM; i++)
    {
        // create page
        simulation->virtualMemory->pages[i] = malloc(sizeof(Page));
        simulation->virtualMemory->pages[i]->offset = malloc(sizeof(Offset*));
        simulation->virtualMemory->pages[i]->residentAddress = i;
        simulation->virtualMemory->pages[i]->pageSize = pageSize;

        // for each offset in a page
        for (int j = 0; j < pageSize; j++)
        {
            // assign the members of the data array
            simulation->virtualMemory->pages[i]->offset[j] = malloc(sizeof(Offset));
            simulation->virtualMemory->pages[i]->offset[j]->value = 0;
            simulation->virtualMemory->pages[i]->offset[j]->residentOffset = j;
        }
    }


    // create page table
    simulation->pageTable = malloc(sizeof(PageTable));
    simulation->pageTable->pageTableEntries = malloc(sizeof(PageTableEntry*));

    // create a page table entry for each page in virtual memory
    for (int i = 0; i < sizeVM; i++)
    {
        // allocate page table entries
        simulation->pageTable->pageTableEntries[i] = malloc(sizeof(PageTableEntry));
        simulation->pageTable->pageTableEntries[i]->virtAddress = i; 
        simulation->pageTable->pageTableEntries[i]->physAddress = -1; 
        simulation->pageTable->pageTableEntries[i]->dirty = 0;
        simulation->pageTable->pageTableEntries[i]->timeStamp = -1;
    }

    simulation->pageTable->pageFaults = 0;
    simulation->pageTable->diskWrites = 0;
    simulation->pageTable->nextAddress = 0;
    simulation->pageTable->time = 0;


    // create physical memory; array of pages
    simulation->physicalMemory = malloc(sizeof(PhysicalMemory));
    simulation->physicalMemory->pages = malloc(sizeof(Page*));

    // for each page in physical memory
    for (int i = 0; i < sizePM; i++)
    {
        // create page
        simulation->physicalMemory->pages[i] = malloc(sizeof(Page));
        simulation->physicalMemory->pages[i]->offset = malloc(sizeof(Offset*));
        simulation->physicalMemory->pages[i]->residentAddress = i;
        simulation->physicalMemory->pages[i]->pageSize = pageSize;

        // for each offset in a page
        for (int j = 0; j < pageSize; j++)
        {
            // assign the members of the data array
            simulation->physicalMemory->pages[i]->offset[j] = malloc(sizeof(Offset));
            simulation->physicalMemory->pages[i]->offset[j]->value = 0;
            simulation->physicalMemory->pages[i]->offset[j]->residentOffset = j;
        }
    }


    // link lowest virtual addresses to lowest physical addresses
    // for each page in physical memory, link to corresponding page in virtual memory
    for (int i = 0; i < sizePM; i++)
    {
        simulation->pageTable->pageTableEntries[i]->physAddress = i;
    }
    
    // return handle
    return simulation;
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
    Simulation *simulation = handle;

    unsigned int virtualPageNumber = address >> 12;
    unsigned int offsetValue = (address << 20) >> 20;

    #if DEBUG
        printf("virtualPageNumber: %d\n", virtualPageNumber);
        printf("offsetValue: %d\n", offsetValue);
        // printf("physicalPageNumber: %d\n", physicalPageNumber);
    #endif
    
    // if page table entry associated with virtual page number leads to an address on disk
    if (simulation->pageTable->pageTableEntries[virtualPageNumber]->physAddress == -1)
    {
        // increment pageFaults
        simulation->pageTable->pageFaults++;

        // move page to physical memory
        // evict page which is next. Evicted page is moved to disk
        simulation->physicalMemory->pages[simulation->pageTable->nextAddress]->residentAddress = -1;

        // increment diskWrites
        simulation->pageTable->diskWrites++;

        // move page requested from disk to physical memory
        
    }

    // if page table entry associated with virtual page number leads to an address in physical memory
    unsigned int translatedAddress = simulation->pageTable->pageTableEntries[virtualPageNumber]->physAddress;
    
    // return the data at the physical address associated with virtual address supplied
    return simulation->physicalMemory->pages[translatedAddress]->offset[offsetValue]->value;
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
    return 0.0;
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
    Simulation *simulation = handle;

    unsigned int virtualPageNumber = address >> 12;
    unsigned int offsetValue = (address << 20) >> 20;
    unsigned int physicalPageNumber = simulation->pageTable->pageTableEntries[virtualPageNumber]->physAddress;

    #if DEBUG
        printf("virtualPageNumber: %d\n", virtualPageNumber);
        printf("offsetValue: %d\n", offsetValue);
        printf("physicalPageNumber: %d\n", physicalPageNumber);
    #endif

    // write it to virtual memory
    // simulation->virtualMemory->pages[virtualPageNumber]->offset[offsetValue]->value = value;

    // write it to physical memory
    // change value from a virtual address
    // go to where virtual address leads
    // if led to the disk: (physical address read from page table is -1)
    if (physicalPageNumber == -1)
    {
        // move page to physical memory:
        // page in disk will be moved to where table says is next
        unsigned int newPageAddress = simulation->pageTable->nextAddress;

        // move page in physical memory to disk
        simulation->physicalMemory->pages[newPageAddress]->residentAddress = -1;

        // edit the page table to show that old 
        simulation->pageTable->pageTableEntries[newPageAddress]->physAddress = -1;        

        // increment diskWrites
        simulation->pageTable->diskWrites++;

        // update next address to be evicted
        simulation->pageTable->nextAddress = (simulation->pageTable->nextAddress + 1) % simulation->physicalMemory->sizePM;
    }
    // if led to page in physical memory: (physical address read from page table is not -1)
    // no need to change page table

    // overwrite value in such physical page at desired offset
    // simulation->physicalMemory->pages[physicalPageNumber]->offset[offsetValue]->value = value;

    #if DEBUG
        // printf("value: %d written to physical memory in page: %d, offset: %d\n", (int) simulation->physicalMemory->pages[physicalPageNumber]->offset[offsetValue]->value, physicalPageNumber, offsetValue);
    #endif
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
    PageTable *pageTable = handle;

    printf("Number of page faults: %d\n", pageTable->pageFaults);
    printf("Number of disk writes: %d\n", pageTable->diskWrites);
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
    PageTable *pageTable = handle;

    free(pageTable->pageTableEntries);
    free(pageTable);
}
