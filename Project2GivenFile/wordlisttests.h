#ifndef PROJECT2_WLTEST_H
#define PROJECT2_WLTEST_H
 
namespace ZeroRelative {

	int test_resize(int testNum);		// cases: 0-6
	int test_ctor(int testNum);			// cases: 0-2
	int test_dtor(int testNum);			// cases: 0 Debugmem
	int test_copyctor(int testNum);		// cases: 0-1
	int test_assignOper(int testNum);	// cases: 0-2, 3 Debugmem
	int test_stored(int testNum);		// cases: 0-1
	int test_space(int testNum);		// cases: 0-3
	int test_display(int testNum);		// cases: 0-2
	int test_insert(int testNum);		// cases: 0-15
	int test_erase(int testNum);		// cases: 0-4
	int test_at(int testNum);			// cases: 0-2
	int test_search(int testNum);		// cases: 0-3
	int test_sort(int testNum);			// cases: 0-9
	int test_interleave(int testNum);	// cases: 0-16
	int test_yoink(int testNum);		// cases: 0-13

}

// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif

#include<assert.h>

#include<iostream>
#include<fstream>
#include<sstream> 
#include<string>
#include<iterator>
#include<vector>

#include<exception>
#include<functional>
#include<algorithm>

#include<cstring>
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

int runTest(std::function<int(int)> test, int testNum) {
	int retval = 0;
	try {
		retval = test(testNum);
	}
	catch (const std::runtime_error& re) {
		std::cerr << "Runtime error: " << re.what() << std::endl;
		retval = 1;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error occurred: " << ex.what() << std::endl;
		retval = 1;
	}
	catch (...) {
		std::cerr << "Unknown failure occurred. Possible memory corruption" << std::endl;
		retval = 1;;
	}
	return retval;
}


#ifdef _MSC_VER 
#define __func__ __FUNCTION__
#endif

#include"debugmem.h"

// Blank out macros if debugmem.h is not included
#ifndef DEBUG_NEW
#define DEBUG_NEW new 
#endif
#ifndef RESET()
#define RESET()
#endif
#ifndef GETMEMORYREPORT()
#define GETMEMORYREPORT()
#endif
#ifndef SIZE()
#define SIZE() 0
#endif

#define MAKE_MEMBERS_PUBLIC
#include"wordlist.h"

//Test implementations based on
//WordLists designed with the zeroth
//element being the Front.
namespace ZeroRelative {

	int test_resize(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup/Test 
			Wordlist *wl = new Wordlist(0);
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			int retval = wl->resize(0);

			// Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);
			assert(retval == -2);
			break;
		}
		case 1: {
			// Setup/Test
			Wordlist *wl = new Wordlist(0);
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int retval = wl->resize(-10);

			// Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);
			assert(retval == -2);

			break;
		}
		case 2: {
			// Setup/Test
			Wordlist *wl = new Wordlist(0);
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int retval = wl->resize(3);

			// Verify Results
			assert(wl->allocated == 3);
			assert(wl->size == 0);
			assert(wl->list != nullptr);
			if (wl->list != nullptr) {
				for (int i = 0; i < 3; i++)
					assert(wl->list[i] != nullptr);
			}
			assert(retval == 1);


			break;
		}
		case 3: {
			// Setup/Test 
			int max = 7,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;


			Wordlist *wl = new Wordlist(0);
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int amt = 0;
			int retval = wl->resize(amt);

			// Verify Results
			assert(wl->allocated == max + amt);
			assert(wl->size == num);
			//assert(retval == 1);
			//assert(wl->list == testlist);
			if (wl->list != nullptr) {
				for (int i = 0; i < wl->allocated; i++)
					assert(wl->list[i] != nullptr);
			}
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);

			break;
		}
		case 4: {
			// Setup/Test 
			int max = 7,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;


			Wordlist *wl = new Wordlist(0);
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int amt = 3;
			int retval = wl->resize(amt);

			// Verify Results
			assert(wl->allocated == max + amt);
			assert(wl->size == num);
			//assert(wl->list == testlist);
			assert(retval == 1);
			if (wl->list != nullptr) {
				for (int i = 0; i < wl->allocated; i++)
					assert(wl->list[i] != nullptr);
			}
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);



			break;
		}
		case 5: {
			// Setup/Test 
			int max = 7,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;


			Wordlist *wl = new Wordlist(0);
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int amt = -3;
			int retval = wl->resize(amt);

			// Verify Results
			assert(wl->allocated == max + amt);
			assert(wl->size == num);
			assert(retval == -1);
			//assert(wl->list == testlist);
			if (wl->list != nullptr) {
				for (int i = 0; i < wl->allocated; i++)
					assert(wl->list[i] != nullptr);
			}
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);



			break;
		}
		case 6: {
			// Setup/Test 
			int max = 7,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;


			Wordlist *wl = new Wordlist(0);
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int amt = -13;
			int retval = wl->resize(amt);

			// Verify Results
			assert(wl->allocated == num);
			assert(wl->size == num);
			assert(retval == -1);
			//assert(wl->list == testlist);
			if (wl->list != nullptr) {
				for (int i = 0; i < wl->allocated; i++)
					assert(wl->list[i] != nullptr);
			}
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);



			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;

		}
		return 0;
	}

	int test_ctor(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup/Test 
			Wordlist *wl = new Wordlist(0);

			// Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);
			break;
		}
		case 1: {
			// Setup/Test
			Wordlist *wl = new Wordlist(-99);

			// Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);

			break;
		}
		case 2: {
			// Setup/Test
			Wordlist *wl = new Wordlist(10);

			// Verify Results
			assert(wl->allocated == 10);
			assert(wl->size == 0);
			assert(wl->list != nullptr);
			if (wl->list != nullptr) {
				for (int i = 0; i < 10; i++)
					assert(wl->list[i] != nullptr);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;

		}
		return 0;
	}


	int test_display(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup Initial State
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);

			// Inject initial state into object being tested
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			std::string test_string1("Tom Dick Mary\n"); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");

			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			//Verify
			assert(retval == 3);
			assert(text.length() == test_string1.length());
			assert(text == test_string1);

			break;
		}
		case 1: {
			//Setup
			Wordlist *wl = new Wordlist(0);
			//Inject
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			std::string test_string1(""); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");

			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke 
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			// Verify
			assert(retval == 0);
			assert(text.length() == test_string1.length());
			assert(text == test_string1);
			break;
		}
		case 2: {
			// Setup Initial State
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];

			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State 
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			std::string test_string1("Tom Dick Mary\n"); //Without lagging space
			std::stringstream buffer(test_string1);
			std::vector<std::string> test_vector{ std::istream_iterator<std::string>(buffer), std::istream_iterator<std::string>() };
			buffer.str("");
			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

			// Invoke 
			int retval = wl->display();

			// Hijack the buffer
			std::cout.rdbuf(old);
			std::string text = buffer.str();
			std::vector<std::string> ret{ std::istream_iterator<std::string>(buffer),
				std::istream_iterator<std::string>() };

			std::stringstream ss(text);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<std::string> vstrings(begin, end);
			std::cout << text << std::endl;

			// Verify
			for (int i = 0; i < std::min(vstrings.size(), test_vector.size()); i++) {
				assert(vstrings[i] == test_vector[i]);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_at(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup Initial State
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(strcmp("Tom", wl->at(0)) == 0);
			assert(strcmp("Dick", wl->at(1)) == 0);
			assert(strcmp("Mary", wl->at(2)) == 0);
			break;
		}
		case 1: {
			// Setup
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->at(100) == nullptr);

			break;
		}
		case 2: {
			// Setup
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->at(-1) == nullptr);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_space(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->space() == 0);
			break;
		}

		case 1: {
			// Setup 
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->space() == max - num);

			break;
		}
		case 2: {
			// Setup 
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}



			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->space() == max - num);

			break;
		}
		case 3: {
			// Setup 
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			strcpy(testlist[3], "Sue");
			strcpy(testlist[4], "Abigail");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->space() == max - num);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
	int test_stored(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->stored() == 0);
			break;
		}
		case 1: {
			// Setup 
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->stored() == num);

			break;
		}

		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_insert(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(0, "Tom") == 1);
			break;
		}
		case 1: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			char *word = new char[5];
			strcpy(word, "Tom");
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke Function to be Verified
			wl->insert(0, "Tom");

			// Verify Results
			assert(wl->allocated == 1);
			assert(wl->size == 1);
			assert(wl->list != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			break;
		}
		case 2: {
			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(0, "") == 1);

			break;
		}
		case 3: {
			// Setup 
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->insert(0, "") == 0);

			break;
		}
		case 4: {
			// Setup 
			int max = 3,
				num = 0;
			char ** testlist = new char*[max];

			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;
			// Invoke and Verify Results
			assert(wl->insert(0, "Jane") == 3);

			break;
		}
		case 5: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");

			int max = 3,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(0, word);

			// Verify Results
			assert(wl->allocated == 6);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Jane", wl->list[0]) == 0);

			assert(wl->list[1] != nullptr);
			assert(wl->list[1] != word);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Tom", wl->list[1]) == 0);

			assert(wl->list[2] != nullptr);
			assert(wl->list[2] != word);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Dick", wl->list[2]) == 0);

			assert(wl->list[3] != nullptr);
			assert(wl->list[3] != word);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp("Mary", wl->list[3]) == 0);

			break;
		}
		case 6: {
			// Setup 
			int max = 5,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->insert(0, "Jane") == 2);

			break;
		}
		case 7: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(0, word);

			// Verify Results
			assert(wl->allocated == 5);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp(word, wl->list[0]) == 0);

			assert(wl->list[1] != nullptr);
			assert(wl->list[1] != word);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Tom", wl->list[1]) == 0);

			assert(wl->list[2] != nullptr);
			assert(wl->list[2] != word);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Dick", wl->list[2]) == 0);

			assert(wl->list[3] != nullptr);
			assert(wl->list[3] != word);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp("Mary", wl->list[3]) == 0);

			break;
		}
		case 8: {
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(-1, "Tom") == 1);
			assert(wl->size == 1);
			assert(wl->allocated == 1);
			assert(strcmp(wl->list[0], "Tom") == 0);
			break;
		}
		case 9: {
			// Setup
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->insert(8, "Tom") == 1);
			assert(wl->size == 1);
			assert(wl->allocated == 1);
			assert(strcmp(wl->list[0], "Tom") == 0);
			break;
		}
		case 10: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(-1, word);

			// Verify Results
			assert(wl->allocated == 5);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp(word, wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Tom", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Dick", wl->list[2]) == 0);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp("Mary", wl->list[3]) == 0);

			break;
		}
		case 11: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(4, word);

			// Verify Results
			assert(wl->allocated == 5);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[3] != nullptr);
			assert(wl->list[3] != word);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp(word, wl->list[3]) == 0);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);

			break;
		}
		case 12: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			int retval = wl->insert(1, word);

			// Verify Results
			assert(retval == 2);
			assert(wl->allocated == 5);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp(word, wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Dick", wl->list[2]) == 0);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp("Mary", wl->list[3]) == 0);

			break;
		}
		case 13: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 3,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			int retval = wl->insert(1, word);

			// Verify Results
			assert(retval == 3);
			assert(wl->allocated == 6);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp(word, wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Dick", wl->list[2]) == 0);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp("Mary", wl->list[3]) == 0);

			break;
		}
		case 14: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 5,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(8, word);

			// Verify Results
			assert(wl->allocated == 5);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp(word, wl->list[3]) == 0);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);

			break;
		}
		case 15: {
			// Setup 
			char *word = new char[5];
			strcpy(word, "Jane");
			int max = 3,
				num = 0;
			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Tom");
			strcpy(testlist[1], "Dick");
			strcpy(testlist[2], "Mary");
			num = 3;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->insert(8, word);

			// Verify Results
			assert(wl->allocated == 6);
			assert(wl->size == 4);
			assert(wl->list != nullptr);
			assert(wl->list[0] != nullptr);
			assert(wl->list[0] != word);
			if (wl->list != nullptr && wl->list[3] != nullptr)
				assert(strcmp(word, wl->list[3]) == 0);
			if (wl->list != nullptr && wl->list[0] != nullptr)
				assert(strcmp("Tom", wl->list[0]) == 0);
			if (wl->list != nullptr && wl->list[1] != nullptr)
				assert(strcmp("Dick", wl->list[1]) == 0);
			if (wl->list != nullptr && wl->list[2] != nullptr)
				assert(strcmp("Mary", wl->list[2]) == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
	int test_erase(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {

			// Setup 
			Wordlist *wl = new Wordlist(0);

			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->erase("Tom") == -3);

			break;
		}
		case 1: {
			// Setup 
			char *word = new char[4];
			strcpy(word, "");

			int max = 10,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->erase(word) == 0);

			break;
		}
		case 2: {

			// Setup 
			int max = 10,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;
			// Invoke and Verify Results
			assert(wl->erase("Wash") == 2);

			break;
		}
		case 3: {
			// Setup 
			int max = 10,
				num = 0;

			char ** testlist = new char*[max];
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->erase("Wash");

			// Verify Results
			assert(wl->size == 6);
			assert(strcmp("Mal", wl->list[0]) == 0);
			assert(strcmp("Inara", wl->list[1]) == 0);
			assert(strcmp("Jayne", wl->list[2]) == 0);
			assert(strcmp("Kaylee", wl->list[3]) == 0);
			assert(strcmp("River", wl->list[4]) == 0);
			assert(strcmp("Book", wl->list[5]) == 0);

			break;
		}
		case 4: {
			// Setup 
			int max = 10, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			strcpy(testlist[4], "Kaylee");
			strcpy(testlist[5], "River");
			strcpy(testlist[6], "Book");
			strcpy(testlist[7], "Wash");
			num = 8;

			Wordlist *wl = new Wordlist(max);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->erase("Operative") == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_search(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->search("Bob") == -2);


			break;
		}
		case 1: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->search("Bob") == -1);
			//assert(wl->allocated == max);

			break;
		}
		case 2: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->search("Mal") == 0);

			break;
		}
		case 3: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->search("Jayne") == 3);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_sort(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {
			// Setup 

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->sort(1) == -2);
			break;
		}
		case 1: {
			// Setup 

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->sort(-1) == -2);
			break;
		}
		case 2: {
			// Setup 

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke and Verify Results
			assert(wl->sort(0) == -2);
			break;
		}
		case 3: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->sort(1) == 0);

			break;
		}
		case 4: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			num = 1;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->sort(0) == 0);

			break;
		}
		case 5: {
			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Door");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Islington");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke and Verify Results
			assert(wl->sort(1) == 1);

			break;
		}
		case 6: {

			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->sort(1);
			//wl->display();
			// Verify Results
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {

				assert(strcmp(wl->list[0], "Abbot") == 0);
				assert(strcmp(wl->list[1], "Carabas") == 0);
				assert(strcmp(wl->list[2], "Door") == 0);
				assert(strcmp(wl->list[3], "Islington") == 0);
				assert(strcmp(wl->list[4], "Richard") == 0);
			}
			break;
		}
		case 7: {

			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->sort(-1);
			//wl->display();
			// Verify Results
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {

				assert(strcmp(wl->list[4], "Abbot") == 0);
				assert(strcmp(wl->list[3], "Carabas") == 0);
				assert(strcmp(wl->list[2], "Door") == 0);
				assert(strcmp(wl->list[1], "Islington") == 0);
				assert(strcmp(wl->list[0], "Richard") == 0);
			}
			break;
		}
		case 8: {

			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[4], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->sort(0);
			//wl->display();
			// Verify Results
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {

				assert(strcmp(wl->list[4], "Abbot") == 0);
				assert(strcmp(wl->list[3], "Carabas") == 0);
				assert(strcmp(wl->list[2], "Door") == 0);
				assert(strcmp(wl->list[1], "Islington") == 0);
				assert(strcmp(wl->list[0], "Richard") == 0);
			}
			break;
		}
		case 9: {

			// Setup 
			int max = 5, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[4], "Richard");
			strcpy(testlist[1], "Islington");
			strcpy(testlist[2], "Carabas");
			strcpy(testlist[3], "Door");
			strcpy(testlist[0], "Abbot");
			num = 5;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			// Invoke Function to be Verified
			wl->sort(0);
			//wl->display();
			// Verify Results
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {

				assert(strcmp(wl->list[0], "Abbot") == 0);
				assert(strcmp(wl->list[1], "Carabas") == 0);
				assert(strcmp(wl->list[2], "Door") == 0);
				assert(strcmp(wl->list[3], "Islington") == 0);
				assert(strcmp(wl->list[4], "Richard") == 0);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_copyctor(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke Function to be Verified
			Wordlist *copy = new Wordlist(*wl);

			// Verify Results
			assert(copy->allocated == 0);
			assert(copy->size == 0);
			assert(copy->list == nullptr);

			break;
		}
		case 1: {
			// Setup 
			int max = 10, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State
			other->allocated = max;
			other->size = num;
			other->list = testlist;


			// Invoke Function to be Verified
			Wordlist *wl = new Wordlist(*other);

			// Verify Results
			assert(wl->size == other->size);
			assert(wl->allocated == other->allocated);
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != other->list);
				for (int i = 0; i < wl->allocated; i++) {
					for (int j = 0; j < other->allocated; j++) {
						assert(wl->list[i] != other->list[j]);
					}
				}
				assert(strcmp(wl->list[0], other->list[0]) == 0);
				assert(strcmp(wl->list[1], other->list[1]) == 0);
				assert(strcmp(wl->list[2], other->list[2]) == 0);
				assert(strcmp(wl->list[3], other->list[3]) == 0);
			}
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_assignOper(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for First Wordlist
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			Wordlist *copy = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			copy->allocated = 0;
			copy->size = 0;
			copy->list = nullptr;

			// Invoke Function to be Verified
			*copy = *wl;


			// Verify Results
			assert(copy->allocated == 0);
			assert(copy->size == 0);
			assert(copy->list == nullptr);


			break;
		}
		case 1: {
			// Setup 
			int max = 10, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->allocated = max;
			other->size = num;
			other->list = testlist;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->size == other->size);
			assert(wl->allocated == other->allocated);
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != other->list);
				for (int i = 0; i < wl->allocated; i++) {
					for (int j = 0; j < other->allocated; j++) {
						assert(wl->list[i] != other->list[j]);
					}
				}
				assert(strcmp(wl->list[0], other->list[0]) == 0);
				assert(strcmp(wl->list[1], other->list[1]) == 0);
				assert(strcmp(wl->list[2], other->list[2]) == 0);
				assert(strcmp(wl->list[3], other->list[3]) == 0);
			}

			break;
		}
		case 2: {
			// Setup 
			int max = 10, // Keep track of the max number list	
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist[0], "Mal");
			strcpy(testlist[1], "Inara");
			strcpy(testlist[2], "Wash");
			strcpy(testlist[3], "Jayne");
			num = 4;


			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->allocated = max;
			other->size = num;
			other->list = testlist;

			int max2 = 5, // Keep track of the max number list	
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;


			Wordlist *wl = new Wordlist(0);
			// Inject Initial State for Second Wordlist
			wl->allocated = max2;
			wl->size = num2;
			wl->list = testlist2;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->size == other->size);
			assert(wl->allocated == other->allocated);
			assert(wl->list != nullptr);
			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != other->list);
				for (int i = 0; i < wl->allocated; i++) {
					for (int j = 0; j < other->allocated; j++) {
						assert(wl->list[i] != other->list[j]);
					}
				}
				assert(strcmp(wl->list[0], other->list[0]) == 0);
				assert(strcmp(wl->list[1], other->list[1]) == 0);
				assert(strcmp(wl->list[2], other->list[2]) == 0);
				assert(strcmp(wl->list[3], other->list[3]) == 0);
			}

			break;
		}
		case 3: {
			// Setup 
			Wordlist *other = new Wordlist(0);
			// Inject Initial State for First Wordlist
			other->allocated = 0;
			other->size = 0;
			other->list = nullptr;

			Wordlist *wl = new Wordlist(0);

			RESET();
			int max2 = 5, // Keep track of the max number list	
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = DEBUG_NEW char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = DEBUG_NEW char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;
			// Inject Initial State for Second Wordlist
			wl->allocated = max2;
			wl->size = num2;
			wl->list = testlist2;

			// Invoke Function to be Verified
			*wl = *other;

			// Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);

			if (SIZE() != 0) {
				std::cerr << "Assign Op: Memory Leak detected" << std::endl;
			}
			assert(SIZE() == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}

	int test_dtor(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);
		switch (testNum) {
		case 0: {
			// Setup 
			RESET();
			int max2 = 5, // Keep track of the max number list	
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = DEBUG_NEW char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = DEBUG_NEW char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "Richard");
			strcpy(testlist2[1], "Islington");
			strcpy(testlist2[2], "Carabas");
			strcpy(testlist2[3], "Door");
			strcpy(testlist2[4], "Abbot");
			num2 = 5;

			{
				Wordlist wl(0);
				// Inject Initial State
				wl.allocated = max2;
				wl.size = num2;
				wl.list = testlist2;

			} // Invoke Function to be Verified

			// Verify Results
			//GETMEMORYREPORT();
			if (SIZE() != 0) {
				std::cerr << "Destructor: Memory Leak detected" << std::endl;
			}
			assert(SIZE() == 0);

			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}


	int test_interleave(int testNum) {

		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {

			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = 0;
			wl2->size = 0;
			wl2->list = nullptr;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == -1);
			break;
		}
		case 1: {


			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = 0;
			wl2->size = 0;
			wl2->list = nullptr;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 0);
			break;
		}
		case 2: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 0);
			break;
		}
		case 3: {

			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == -1);
			break;
		}
		case 4: {

			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == -1);
			break;
		}
		case 5: {

			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == 1);
			assert(wl->size == 1);
			assert(wl->list != nullptr);


			if (wl->list != nullptr)
				assert(strcmp("mia", wl->list[0]) == 0);

			break;
		}
		case 6: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 1);

			break;
		}
		case 7: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);
			if (wl->list != nullptr) {
				assert(wl->list[0] != nullptr);
				if (wl->list[0] != nullptr)
					assert(strcmp("mia", wl->list[0]) == 0);
			}
			break;
		}
		case 8: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			num = 1;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 1);
			break;
		}
		case 9: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			num = 1;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("mia", wl->list[1]) == 0);


			break;
		}
		case 10: {

			// Setup 
			int max = 1, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			num = 1;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 1);
			break;
		}
		case 11: {

			// Setup 
			int max = 1, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			num = 1;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "mia");
			num2 = 1;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == 2 * max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("mia", wl->list[1]) == 0);
			break;
		}
		case 12: {

			// Setup 
			int max = 5, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			strcpy(testlist[1], "holmes");
			strcpy(testlist[2], "dean");
			num = 3;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "suzannah");
			strcpy(testlist2[1], "mia");
			num2 = 2;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 2);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("suzannah", wl->list[1]) == 0);
			assert(strcmp("holmes", wl->list[2]) == 0);
			assert(strcmp("mia", wl->list[3]) == 0);
			assert(strcmp("dean", wl->list[4]) == 0);

			break;
		}
		case 13: {

			// Setup 
			int max = 3, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			strcpy(testlist[1], "holmes");
			strcpy(testlist[2], "dean");
			num = 3;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 2, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "suzannah");
			strcpy(testlist2[1], "mia");
			num2 = 2;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == 2 * max);
			assert(wl->size == num + 2);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("suzannah", wl->list[1]) == 0);
			assert(strcmp("holmes", wl->list[2]) == 0);
			assert(strcmp("mia", wl->list[3]) == 0);
			assert(strcmp("dean", wl->list[4]) == 0);
			break;
		}
		case 14: {

			// Setup 
			int max = 8, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			strcpy(testlist[1], "holmes");

			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 5, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "suzannah");
			strcpy(testlist2[1], "mia");
			strcpy(testlist2[2], "dean");
			strcpy(testlist2[3], "walker");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 4);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("suzannah", wl->list[1]) == 0);
			assert(strcmp("holmes", wl->list[2]) == 0);
			assert(strcmp("mia", wl->list[3]) == 0);
			assert(strcmp("dean", wl->list[4]) == 0);
			assert(strcmp("walker", wl->list[5]) == 0);
			break;
		}
		case 15: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			strcpy(testlist[1], "holmes");

			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 5, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "suzannah");
			strcpy(testlist2[1], "mia");
			strcpy(testlist2[2], "dean");
			strcpy(testlist2[3], "walker");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(retval == 4);
			break;
		}
		case 16: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "odetta");
			strcpy(testlist[1], "holmes");

			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 5, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}
			// Initialize list
			strcpy(testlist2[0], "suzannah");
			strcpy(testlist2[1], "mia");
			strcpy(testlist2[2], "dean");
			strcpy(testlist2[3], "walker");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke  
			int retval = wl->interleave(*wl2);

			// Verify Results
			assert(wl->allocated == 4 * max);
			assert(wl->size == num + 4);
			assert(wl->list != nullptr);


			for (int i = 0; i < wl->size; i++) {
				assert(wl->list[i] != nullptr);
				if (wl->list[i] == nullptr)
					return -1;
			}
			if (wl->list != nullptr) {
				assert(wl->list != wl2->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
					}
				}

			}
			assert(strcmp("odetta", wl->list[0]) == 0);
			assert(strcmp("suzannah", wl->list[1]) == 0);
			assert(strcmp("holmes", wl->list[2]) == 0);
			assert(strcmp("mia", wl->list[3]) == 0);
			assert(strcmp("dean", wl->list[4]) == 0);
			assert(strcmp("walker", wl->list[5]) == 0);
			break;
		}
		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}

		return 0;
	}
	int test_yoink(int testNum) {
		std::cout << std::endl << std::endl;
		std::cout << __func__ << testNum << std::endl;
		std::string name = std::string(__func__);

		switch (testNum) {
		case 0: {



			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = 0;
			wl2->size = 0;
			wl2->list = nullptr;

			// Invoke and Verify Results
			int retval = wl->yoink("Tom", *wl2);
			assert(retval == -1);
			break;

		}
		case 1: {


			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			// Invoke and Verify Results
			int retval = wl->yoink("Tom", *wl2);

			assert(retval == -1);
			break;

		}
		case 2: {


			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("Tom", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2);

			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("ikalgo", wl2->list[1]) == 0);
			assert(strcmp("flutter", wl2->list[2]) == 0);
			assert(strcmp("cheetu", wl2->list[3]) == 0);
			break;

		}
		case 3: {



			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("", *wl2);

			// Invoke and Verify Results
			assert(retval == -1);
			break;

		}
		case 4: {


			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == 0);
			assert(wl->size == 0);
			assert(wl->list == nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2);

			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("ikalgo", wl2->list[1]) == 0);
			assert(strcmp("flutter", wl2->list[2]) == 0);
			assert(strcmp("cheetu", wl2->list[3]) == 0);
			break;

		}
		case 5: {



			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(retval == 1);
			break;

		}
		case 6: {


			// Setup 
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = 0;
			wl->size = 0;
			wl->list = nullptr;


			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;


			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == 1);
			assert(wl->size == 1);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2 - 1);

			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("ikalgo", wl->list[0]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("flutter", wl2->list[1]) == 0);
			assert(strcmp("cheetu", wl2->list[2]) == 0);
			break;

		}
		case 7: {



			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(retval == 0);
			break;

		}
		case 8: {


			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2 - 1);

			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("ikalgo", wl->list[0]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("flutter", wl2->list[1]) == 0);
			assert(strcmp("cheetu", wl2->list[2]) == 0);
			break;

		}
		case 9: {

			// Setup 
			int max = 2, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "gon");
			strcpy(testlist[1], "kilua");
			num = 2;

			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("netero", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2);
			assert(wl2->list != nullptr);
			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("gon", wl->list[0]) == 0);
			assert(strcmp("kilua", wl->list[1]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("ikalgo", wl2->list[1]) == 0);
			assert(strcmp("flutter", wl2->list[2]) == 0);
			assert(strcmp("cheetu", wl2->list[3]) == 0);

			break;
		}
		case 10: {

			// Setup 
			int max = 3, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "gon");
			strcpy(testlist[1], "kilua");
			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(retval == 0);

			break;
		}
		case 11: {

			// Setup 
			int max = 3, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "gon");
			strcpy(testlist[1], "kilua");
			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2 - 1);
			assert(wl2->list != nullptr);
			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("gon", wl->list[0]) == 0);
			assert(strcmp("kilua", wl->list[1]) == 0);
			assert(strcmp("ikalgo", wl->list[2]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("flutter", wl2->list[1]) == 0);
			assert(strcmp("cheetu", wl2->list[2]) == 0);
			break;
		}
		case 12: {

			// Setup 
			int max = 4, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "gon");
			strcpy(testlist[1], "kilua");
			strcpy(testlist[2], "knuckle");
			strcpy(testlist[3], "shoot");
			num = 4;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 4, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "cheetu");
			num2 = 4;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == 2 * max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2 - 1);
			assert(wl2->list != nullptr);
			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("gon", wl->list[0]) == 0);
			assert(strcmp("kilua", wl->list[1]) == 0);
			assert(strcmp("knuckle", wl->list[2]) == 0);
			assert(strcmp("shoot", wl->list[3]) == 0);
			assert(strcmp("ikalgo", wl->list[4]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("flutter", wl2->list[1]) == 0);
			assert(strcmp("cheetu", wl2->list[2]) == 0);
			break;
		}
		case 13: {

			// Setup 
			int max = 3, // Keep track of the max number list
				num = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist = new char*[max];
			// for each row, allocate space for list
			for (int i = 0; i < max; i++) {
				testlist[i] = new char[20];
			}
			strcpy(testlist[0], "gon");
			strcpy(testlist[1], "kilua");
			num = 2;
			Wordlist *wl = new Wordlist(0);
			// Inject Initial State
			wl->allocated = max;
			wl->size = num;
			wl->list = testlist;

			int max2 = 6, // Keep track of the max number list
				num2 = 0; // Number of list we can currently store
			//Allocate rows, to point to list
			char ** testlist2 = new char*[max2];
			// for each row, allocate space for list
			for (int i = 0; i < max2; i++) {
				testlist2[i] = new char[20];
			}

			// Initialize list
			strcpy(testlist2[0], "welfin");
			strcpy(testlist2[1], "ikalgo");
			strcpy(testlist2[2], "flutter");
			strcpy(testlist2[3], "ikalgo");
			strcpy(testlist2[4], "cheetu");
			num2 = 5;

			Wordlist *wl2 = new Wordlist(0);
			// Inject Initial State
			wl2->allocated = max2;
			wl2->size = num2;
			wl2->list = testlist2;

			int retval = wl->yoink("ikalgo", *wl2);

			// Invoke and Verify Results
			assert(wl->allocated == max);
			assert(wl->size == num + 1);
			assert(wl->list != nullptr);

			assert(wl2->allocated == max2);
			assert(wl2->size == num2 - 1);
			assert(wl2->list != nullptr);
			for (int i = 0; i < wl2->size; i++) {
				assert(wl2->list[i] != nullptr);
				if (wl2->list[i] == nullptr)
					return -1;
			}
			if (wl2->list != nullptr) {
				assert(wl2->list != wl->list);
				for (int i = 0; i < wl2->size; i++) {
					for (int j = 0; j < wl->size; j++) {
						assert((wl2->list[i] != wl->list[j]));
						//assert(strcmp(wl2->list[i], wl->list[j]) != 0);
					}
				}

			}
			assert(strcmp("gon", wl->list[0]) == 0);
			assert(strcmp("kilua", wl->list[1]) == 0);
			assert(strcmp("ikalgo", wl->list[2]) == 0);

			assert(strcmp("welfin", wl2->list[0]) == 0);
			assert(strcmp("flutter", wl2->list[1]) == 0);
			assert(strcmp("ikalgo", wl2->list[2]) == 0);
			assert(strcmp("cheetu", wl2->list[3]) == 0);
			break;
		}

		default:
			std::cout << __func__ << " No Such Test: " << testNum << std::endl << std::flush;
			return -1;
		}
		return 0;
	}
}// namespace ZeroRelative
#endif
