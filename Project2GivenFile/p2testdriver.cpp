
#include"wordlisttests.h" 

//Test implemetations based on the "Front"
//defined as the zeroth element.
using namespace ZeroRelative;

int main() {

	runTest(test_ctor, 0);
	//runTest(test_ctor, 1);
	//runTest(test_ctor, 2);

	//runTest(test_display, 0); 
	//runTest(test_display, 1); 
	//runTest(test_display, 2); 

	//runTest(test_at, 0); 
	//See header file for more tests

	//runTest(test_insert, 0); 
	//See header file for more tests

//These two tests use the memory debugger
//Disable if debugmem.h not included.
#ifdef DEBUGMEM_H // if debugmem.h is included 
	//runTest(test_assignOper, 3); //DEBUGMEM_H

	//runTest(test_dtor, 0); //DEBUGMEM_H
#endif

	return 0;
}
