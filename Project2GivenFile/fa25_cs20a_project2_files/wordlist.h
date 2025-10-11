/* Wordlist header file
*
*	This file contains the class definition for the Wordlist.  
*
*	Do not make any changes to this file.
*
*	Do not submit this file
*
*	Topics: Multilevel Arrays, Pointers, Dynamic Allocation, Classes
* 
*/
#ifndef WORDLlST_H
#define WORDLlST_H

// Uncomment this if you want to play with memory tracer
//#include"debugmem.h" 


// All words are at most 19 characters + '\0'
const int MAX_WORD_SIZE = 20;

//	Wordlist ADT
class Wordlist {

#ifdef MAKE_MEMBERS_PUBLIC 
	// If this macro is defined prior to including this header file
	// The private members below will be designated as public, which
	//  will make is more convenient to test and debug.
public:
#endif
	int		size;		// Number of list currently stored in list
	int		allocated;	// The total size of the list.
	char**	list;		// The list storing the list

public:
	Wordlist(const int max);

	Wordlist(const Wordlist &src);

	Wordlist& operator=(const Wordlist &src);

	~Wordlist();

	int		resize(int amt);

	int		display() const; 

	int		stored() const;

	int		space() const;

	const char*	at(const int index) const;

	int		insert(const int index, const char word[]);

	int		erase(const char word[]); 

	int		interleave(const Wordlist &other);

	int		search(const char word[]) const;
	
	int		sort(const int mode);

	int		yoink(const char word[], Wordlist &other);

};


#endif