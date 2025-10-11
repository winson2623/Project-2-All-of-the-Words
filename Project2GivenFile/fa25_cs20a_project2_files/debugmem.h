#ifndef DEBUGMEM_H
#define DEBUGMEM_H 
#include"memorymanager.h"
/*
Basic dynamic memory tracer: works by replacing new/delete, new[]/delete[] with
		overloaded versions that track the addresses of the allocated memory.

Usage:	All three files: debugmem.h, memorymanager.cpp/.h must be present in project.
		Include debugmem.h in all files that calls new and delete, do not
		explicity include memorymanager.h.  memorymanager.cpp/.h only need to be present
		in the project, you do not need to do anything or call any function within them.

		Everything is handled with the inclusion of debugmem.h.  

		Replace all calls to 'new' you want to track with DEBUG_NEW. That is to say you  
		might not want to track everything at once as it will make reading the memory  
		report difficult.

		To get a report of the current allocations call GETMEMORYREPORT().

		Once complete with tracing of allocations, remove all calls to debugmem routines. 
		removing all instances of debugmem.h inclusions will prompt the compiler to identify
		all such routine calls as syntax errors for easy removal.
*/

// Check for current allocations
#define GETMEMORYREPORT() memoryReport()

// Reset the number of tracked allocations, does not deallocate
#define RESET() reset()

// Get the number of tracked allocations
#define SIZE() getNumAlloc()

#define DEBUG_NEW new(__FILE__, __func__, __LINE__)

#endif