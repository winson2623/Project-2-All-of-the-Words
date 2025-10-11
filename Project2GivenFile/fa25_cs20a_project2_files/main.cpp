/* Project 2 main
*
*	Do not submit this file
* 
*/

// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif


/* Main functions
*
*	you may make any changes you want to main to test your functions.
*	We will be using our own to grade.
*
*	I'm using preprocessor directives to layout different mains to test
*	various functions.  I have 5 example mains.  You can insert or replace, 
*	these are here just to illustrate the technique. Cleaner than 
*	commenting/uncommenting blocks of code.
*
*/

// Choose which run to compile
#define RUN1 //RUN1 RUN2 RUN3 RUN4 RUN5

#ifdef RUN0 

// Make sure you understand the tools being used prior to building anything with them.  
// In this case, the functions to manipulate cstrings will be part of your tool set. 
// Might be a good idea to read the section and run some simple programs from the cstring
// section of the spec.

// It is also important to get in the habit of being able to think/implement/test incrementally.
// Break up your tasks into smaller componenets and test as much as possible.  You can think of
// this as a universal law of programming: "The number of bugs grows exponentially with amount of 
// code typed between testing." 

#include"studentinfo.h"

#include<iostream>
using std::cout;
using std::endl;

#include<cstring>
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

int main() {
	//** Setup initial state 
	cout << StudentInfo::Name() << endl;
	cout << StudentInfo::ID() << endl;

	int max = 5, // Keep track of the max number list	
		num = 0; // Number of list we can currently store
	//Allocate rows, to point to list
	char ** testlist = new char*[max];
	// for each row, allocate space for list
	for (int i = 0; i < max; i++) {
		testlist[i] = new char[20];
	}
	
	// Initialize list
	strcpy(testlist[0], "harry");
	strcpy(testlist[1], "ron");
	strcpy(testlist[2], "hermione");
	num = 3;	// Must be consistent with intended state, 
				// e.g. there are three currently three list.

	//*** Begin code for function operator
	 
	//STEP 1  of Algorithm
	//...

	//Test STEP 1
	//...

	//STEP 2 of Algorithm
	//...

	//Test STEP 2
	//...

	return 0;
}

#elif defined RUN1  //Test constructor 


#define MAKE_MEMBERS_PUBLIC // This constant will be checked in worlist.h

#include"wordlist.h"
#include<iostream>

#include<assert.h>
using std::cout;
using std::endl;

int main() {

	//Wordlist wordlist(5);

	// Assuming we made our member variables public:
	//cout << "Count: " << wordlist.size << endl; // Expect 0

	//cout << "Capacity: " << wordlist.allocated << endl; // Expect 5
	

	Wordlist wordlist1(0);
	wordlist1.insert(0, "mia");
	wordlist1.insert(0, "susannah"); // size 2, allocated 2
	Wordlist wordlist2(4);
	wordlist2.insert(0, "dean");
	wordlist2.insert(0, "holmes");
	wordlist2.insert(0, "odetta"); // size 3, allocated 4
	int retval = wordlist2.interleave(wordlist1);
	wordlist2.display(); // display ¡§odetta susannah holmes mia dean\n¡¨
	// Assuming member variables are public
	cout << retval << " " << wordlist2.size << " " << wordlist2.allocated;
	//displays 2 5 8

	
	return 0;

} 
#elif defined RUN2 


#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"


#include<assert.h>

// Same as above but using asserts instead of cout
//
// asserts are a way to check conditions, they will gracefully crash
// the program if the condition is not met.  
//
// This assumes you know what the end state after the function call
// should be.  Effective programmers have in mind test cases prior to 
// implmentation.  You should know what the end state should be after
// any function call.
int main() {
	Wordlist *wordlist = new Wordlist(5);

	// Assuming we made our member variables public:
	// If we failed to set our member variables correctly 
	// These assertions will fail
	assert(wordlist->size == 0);
	assert(wordlist->allocated == 5);
	

	return 0;
}
#elif defined RUN3

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<iostream>
using std::cout;
using std::endl;

// Test insert: Both Constructor and insert must be
// implmented prior to running this code, otherwise
// it will crash.
int main() {
	Wordlist *wordlist = new Wordlist(5);
	wordlist->insert(0, "harry");
	wordlist->insert(0, "ron");
	wordlist->insert(0, "hermione");
	
	cout << wordlist->list[0];

	// Assuming we made our member variables public:
	//cout  << wordlist->list[0][2] << endl; // Expect 'r'

	//cout  << wordlist->list[1] << endl; // Expect "ron"

	return 0;
}

#elif defined RUN4

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"
#include<assert.h>
#include<cstring>

using std::strcmp;
// Test insert: same as RUN3 but with asserts. Both Constructor and insert 
// must be implmented prior to running this code, otherwise it will crash.
int main() {

	Wordlist *wordlist = new Wordlist(5);
	wordlist->insert(0, "harry");
	wordlist->insert(0, "ron");
	wordlist->insert(0, "hermione");
	
	// Assuming we made our member variables public:
	assert(wordlist->list[0][2] == 'r' ); // Individual character, can use == 

	assert(strcmp(wordlist->list[1], "ron") == 0); // cstring, must use strcmp
	
	return 0;
}
#else

// Playing with memory tracer.  For this to work you have to uncomment
// #include"debugmem.h"  in wordlist.h to have the memory tracer included
// into the project, 
//
// Assumes the Constructor, insert are correctly implemented.  Note if there is 
// undefined behavior in any of your code then all bets are off, your code 
// may "appear" correct, may crash, may generate nonesense, all are equally 
// incorrect.  
// 
#define MAKE_MEMBERS_PUBLIC

#include"debugmem.h"
#include"wordlist.h"

#include<iostream>
using std::cout;
using std::endl;

#include<assert.h>

int main() {

	Wordlist * existinglist = DEBUG_NEW Wordlist(5); // Wordlist can store 5 list

	//... Some Wordlist operations
	existinglist->insert(0, "harry");
	existinglist->insert(0, "ron");
	existinglist->insert(0, "hermione");

	GETMEMORYREPORT();
	cout << "------------------------" << endl;
	if (true) {
		Wordlist newList(*existinglist); // Copy Constructor
		GETMEMORYREPORT();

	} // Should not result in memory leaks or undefined behavior 


	delete existinglist; 
	GETMEMORYREPORT();
	cout << "------------------------" << endl;

	return 0;
}

#endif

