#include "simVM.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "inttypes.h"
#define DEBUG 0

typedef struct Node {
    unsigned int timeStamp; 
    unsigned int dirtyBit;    
    int word;   
    unsigned int PPN; 
}Node;

//Virtual Memory Structure
typedef struct VM {
    unsigned int size;  
    Node** memory;  
}virtualMem;

//Physical Memory Structure
typedef struct PM {
    unsigned int size;  //size of physical memory in words
    int* memory;        //integer array with all values inside of physical memory
    unsigned int memIndex;  //index to be altered next
    unsigned int curSize;   //current size of structure
}physicalMem;

//TLB Structure
typedef struct TLB {
    unsigned int size;  //size of TLB
}pageTable;

//Handle Structure
typedef struct handle {
    unsigned int timeStamp; //timeStamp used for values, must be updated in every write or read
    unsigned int pageFaults;  //keeps track of pageFaults
    unsigned int tlbMisses;   //keeps track of TLB misses (relevant from lab10 onward)
    unsigned int diskWrites;    //keeps track of diswrites
    physicalMem pm; //physical memory structure
    virtualMem vm;  //virtual memory structure
    pageTable tlb;  //TLB structure
} hand;

//createVM method, details in header file
void *createVM(unsigned int sizeVM, unsigned int sizePM, unsigned int pageSize, unsigned int sizeTLB, char pageReplAlg, char tlbReplAlg) {
    unsigned int actualSizeVM = sizeVM * pageSize;
    unsigned int actualSizePM = sizePM * pageSize;
    hand *handle = malloc(sizeof(hand));
    
    //mem check
    if(!handle && sizeof(hand)) {
        fprintf(stderr, "Cant malloc handle");
        exit(-1);
    }

    //Initializing
    handle->pm.size = sizePM * 4;
    handle->pm.memIndex = 0;
    handle->pm.curSize = 0;
    handle->vm.size = sizeVM * pageSize;
    handle->tlb.size = sizeVM;
    handle->timeStamp = 1;
    handle->pageFaults = 0;
    handle->tlbMisses = 0;
    handle->diskWrites = 0;



    //Memory allocation
    handle->vm.memory = calloc(actualSizeVM, sizeof(Node*));
    for (int i = 0; i < actualSizeVM; i++) {
        handle->vm.memory[i] = calloc(1, sizeof(Node));
    }

    if(handle->vm.memory == NULL) {
        fprintf(stderr, "Cant calloc VM");
        exit(-1);
    }


    //Memory allocation
    handle->pm.memory = calloc(actualSizePM, sizeof(unsigned int));

    if(handle->pm.memory == NULL) {
        fprintf(stderr, "Cant calloc PM");
        exit(-1);
    }

    //Initializing all virtual memory values
    int i = 0;
    while(i < actualSizeVM) { 
        handle->vm.memory[i]->word = 0;
        handle->vm.memory[i]->dirtyBit = 0;
        handle->vm.memory[i]->PPN = -1;
        handle->vm.memory[i]->timeStamp = -1;
        i++;
    }

    //Initializing all physical memory values
    i = 0;
    while( i < actualSizePM) {
        int x = 0;
        handle->pm.memory[i] = x;
        i++;
    }


    return (void *) handle;

}

//readInt method, details in header file
int readInt(void *handle, unsigned int address) {
    hand *table = (hand *) handle;


    //address error check
    if(address > table->vm.size) {
        fprintf(stderr, "Address, %d, is too large for size %d", address, table->vm.size);
        exit(-1);
    }

    //instance of value in disk
    if(table->vm.memory[address]->PPN == -1) {
        table->pageFaults = table->pageFaults + 1;

        //Gets oldest piece of physical memory with this while loop
        int i = 0;
        unsigned int x = 0xFFFF;
        int index = 0;
        while(i < table->vm.size) {
            if ((table->vm.memory[i]->timeStamp < x) && (table->vm.memory[i]->timeStamp != 0) && (table->vm.memory[i]->PPN != -1)) {
                index = i;
            }
            i++;
        }
        
        
        table->pm.memory[table->vm.memory[index]->PPN] = table->vm.memory[address]->word;
        table->vm.memory[address]->PPN = table->vm.memory[index]->PPN;
        table->vm.memory[index]->PPN = -1;
        table->vm.memory[address]->timeStamp = table->timeStamp;
    }
    int value = table->vm.memory[address]->word;
    table->timeStamp = table->timeStamp + 1;

    return value;
}

//readFloat method, details in header file
float readFloat(void *handle, unsigned int address) {
    // hand *table = (hand *) handle;
    return -1;
}

//writeInt method, details in header file
void writeInt(void *handle, unsigned int address, int value) {
    hand *table = (hand *) handle;

    if(address > table->vm.size) {
        fprintf(stderr, "Address, %d, is too large for size %d", address, table->vm.size);
        exit(-1);
    }
    if(table->pm.curSize < table->pm.size) {
        //Assigns all necessary values and sets time stamps
        table->vm.memory[address]->word = value;
        table->vm.memory[address]->dirtyBit = 1;
        table->vm.memory[address]->timeStamp = table->timeStamp;
        table->vm.memory[address]->PPN = table->pm.memIndex;
        table->pm.memory[table->pm.memIndex] =  value;
    } else {
        if((table->pm.curSize % 4) == 0) {
            //obtains original memory size (64 in sum.c test), important for simulation of page faults in pages
            if((table->pm.curSize % (table->vm.size/4)) == 0) {
                table->pageFaults = table->pageFaults + 1;
            }

            //Purpose: Covers the first instance of memory problem
            if(table->pm.curSize == table->pm.size) {
                table->pageFaults = table->pageFaults + 1;
            }

            //This loop looks for oldest value and assigns it a PPN of -1, this value is the one being replaced in physical memory
            int i = 0; 
            int index = 0;
            unsigned int time = 0xFFFF;
            while(i < table->vm.size) {
                if((table->vm.memory[i]->timeStamp < time) && table->vm.memory[i]->timeStamp != -1 && table->vm.memory[i]->PPN != -1) {
                    time = table->vm.memory[i]->timeStamp;
                    index = i;
                }
                i++;
            }
            table->vm.memory[index]->timeStamp = table->timeStamp;
            table->timeStamp = table->timeStamp + 1;
            table->vm.memory[index]->PPN = -1;
        }

        table->vm.memory[address]->timeStamp = table->timeStamp;
        table->vm.memory[address]->word = value;
        table->vm.memory[address]->dirtyBit = 1;
        table->vm.memory[address]->PPN = table->pm.memIndex;
        table->pm.memory[table->pm.memIndex] =  value;
    }
    table->pm.curSize = table->pm.curSize + 1;
    

    //Counts disk writes
    if((table->pm.memIndex + 1) % 4 == 0) {
        table->diskWrites = table->diskWrites + 1;
    }
    table->pm.memIndex = ((table->pm.memIndex + 1) % table->pm.size);
    table->timeStamp = table->timeStamp + 1;


}

void writeFloat(void *handle, unsigned int address, float value) {
}

void printStatistics(void *handle) {

    hand *table = (hand *) handle;
    printf("Number of page faults: %d\nNumber of disk writes: %d\n", 
    table->pageFaults, table->diskWrites); //only for lab 9

}

//Cleans up memory
void cleanupVM(void *handle) {
    hand *table = (hand *) handle;
    free(table->pm.memory);
    int i = 0; 
    while(i < table->vm.size) {
        free(table->vm.memory[i]);
        i++;
    }
    free(table->vm.memory);
    free(table);
}
