/* Wordlist source file
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias list in any way that would result
*	in undefined behavior. 
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
* 
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif
#define WORDLIST_H

#ifdef ONLINE_HELP
#define CLASS_PROJECT
#include"self_sabotage.h"
#else
// Do not include any other libraries
#define MAKE_MEMBERS_PUBLIC

#include"wordlist.h"
#include<iostream>
#include<cstring>
using std::cout;
using std::endl;
using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;
#endif

// Function:  resize
int Wordlist::resize(int amt) {

	int newAllocated = allocated + amt;

	//EDGE CASES
	
	if (newAllocated <= 0) {        // treat 0 or negative as invalid when size==0
		if (size == 0) { return -2; }
		else { return -1; }
	}
	if (newAllocated < size) { return -1; }

	char** newList = new char* [newAllocated];	//creates new dynamically allocated list with the increased allocated amount

	if (list != nullptr) {
		for (int i = 0; i < size; i++) {	//loops through size and copies contents of old list to new list
			newList[i] = list[i];
		}
	}

	for (int i = size; i < newAllocated; i++) { //makes the remaining new list slots empty
		newList[i] = new char[20];	//allocate memory for strings
		newList[i][0] = 0;	//make them empty
	}

	if (list != nullptr) {
	delete[] list;	//free memory of old list
	}

	list = newList;
	allocated = newAllocated;
	return 1;
	
}

// Function: Wordlist Constructor
Wordlist::Wordlist(const int cap) {
	size = 0;
	if (cap < 1) {
		allocated = 0;
		list = nullptr;
	}
	else {
		allocated = cap;	//make allocated = input (max)
		list = new char*[allocated];	//create dynamic list with allocated array
		for (int i = 0; i < allocated; i++) {
			list[i] = new char[20];	//allows 20 characters in each list including one \0
			list[i][0] = 0;	//each word inside list put empty string
		}
	}
}

// Function: Wordlist Copy Constructor
Wordlist::Wordlist(const Wordlist &other) { 
	//shallow copy
	size = other.size;
	allocated = other.allocated;

	//deep copy list with new memory
	list = new char* [allocated];
	for (int i = 0; i < allocated; i++) { list[i] = nullptr; }	//empties uninitialized list

	for (int i = 0; i < size; i++) {
		list[i] = new char[strlen(other.list[i]) + 1];	//allocate new memory including \0 null
		strcpy(list[i], other.list[i]);	//copy contents in list
	}
}

// Funtion: Assignment Operator
Wordlist& Wordlist::operator=(const Wordlist &other) {
	//EDGE CASE IF same then return this
	if (this == &other) { return *this; }

	//DESTRUCTOR clears list
	for (int i = 0; i < allocated; i++) {	
		if (list[i] != nullptr) {	
			delete[] list[i];
		}
	} delete[] list;
	
	//EDGE CASE IF empty list
	if (other.list == nullptr) {
		list = nullptr;
		size = 0;
		allocated = 0;
		return *this;
	}

	//SHALLOW COPY
	size = other.size;
	allocated = other.allocated;

	//DEEP COPY
	list = new char* [allocated];
	for (int i = 0; i < allocated; i++) { list[i] = nullptr; }	//empties uninitialized list

	for (int i = 0; i < size; i++) {
		list[i] = new char[strlen(other.list[i]) + 1];	//allocate new memory including \0 null
		strcpy(list[i], other.list[i]);	//copy contents in list
	}

	return *this;

}

// Function: Wordlist Destructor.
Wordlist::~Wordlist() {
	for (int i = 0; i < allocated; i++) {	//loops through all allocated memory
		if (list[i] != nullptr) {			//if the index in list has word, delete that word in list
			delete[] list[i];
		}
	}
	delete[] list;	//then delete all of the list itself
}

// Function: display
int	Wordlist::display() const {
	if (list == nullptr || size == 0) {
		return 0;
	}
	for (int i = 0; i < size; i++){
		cout << list[i];

		if (i < size - 1) {//doesn't print the extra space at the end
			cout << " ";
		}
	}
	cout << endl;
	return size;
}

// Function: at
const char* Wordlist::at(const int index) const {
	if (index >= 0 && index < size) {
		return list[index];
	}
	else {
		return nullptr;
	}
}

// Function: stored
int	Wordlist::stored() const {
	if (list == nullptr) { return 0; }

	return size;
}

// Function: space
int	Wordlist::space() const {
	if (list == nullptr) { return 0; }

	int spaceCount = 0;
	for (int i = 0; i < allocated; i++) {
		if (list[i] == nullptr) {
			spaceCount++;
		}
	}
	
	return spaceCount;
}

// Function: insert
int	Wordlist::insert(const int index, const char word[]) {
	
	if (strlen(word) == 0) { return 0; }

	if (list == nullptr && allocated > 0) {
		return 1;
	}

	bool resized = false;
	if (size == allocated) {
		resize(1); // ensure space
		resized = true;
	}

	int position = index;
	if (position < 0) { position = 0;}
	if (position > size) { position = size; }

	for (int i = size - 1; i >= position; --i) {	//loop starting from end of size and decrementing
		list[i + 1] = list[i];				//moves list by 1, list[0+1] = list[1]
	}

	list[position] = new char[strlen(word) + 1];
	strcpy(list[position], word);
	size++;
	
	
	if (resized) {
		return 3;
	}
	else {
		return 2;
	}
}

// Funtion: erase
int	Wordlist::erase(const char word[]) {
	if (list == nullptr) {
		return -3;
	}
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(word, list[i]) == 0) {
			delete[] list[i];
			list[i] = 0;
			for (int j = i; j < size - 1; j++) {
				list[j] = list[j + 1];
			}
			size--;
			count++;
			list[size] = nullptr;
			i--;
		}
	}
	
	return count;

}

// Function: interleave
int	Wordlist::interleave(const Wordlist &other){
	if (list == nullptr) { return -1;}
	if (other.list == nullptr) { return 0; }

	if (allocated < size + other.size) {
		resize(size + other.size - allocated);
	}


	int position = 1;
	for (int i = 0; i < other.size; i++) {
		insert(position, other.list[i]);
		position += 2;
	}
	return other.size;
}

// Function: search
int Wordlist::search(const char word[]) const {
	if (list == nullptr) { return -2; }

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < strlen(list[i]); ++j) {
			list[i][j] = tolower(list[i][j]);
		}// THIS CHANGES THE ORIGINAL LIST TO ALL LOWERCASE, create new memory and copy it to temp, to prevent overriding INFO

		int result = strcmp(list[i], word);
		if (result == 0) {
			return i;
		}
	}
	return -1;
}

// Funtion: sort
int	Wordlist::sort(const int mode) {
	if (list == nullptr) { return -2; }

	if (mode == 0) {
		if (list[0] >= list[size - 1]) {
			mode == 1;
		}
		else {
			mode == -1;
		}
	}

	if (mode == 1) {
		return 1;
	}

	if (mode == -1) {
		for (int i = 0; i < size/2; ++i) {	//starts looping from 0 to center
			char* temp = list[i];
			list[i] = list[size - 1 - i];	//put end of list item to the front
			list[size - 1 - i] = temp;		//puts the temp to the back of the list

		}
	}
	return 1;
}
// Funtion: yoink
int	Wordlist::yoink(const char word[], Wordlist &other) {
	
	// --- TODO --- 
	int dummyreturnval = -9000;
	return dummyreturnval;

}
