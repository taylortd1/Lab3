#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramList.h"
#include "NgramFast.h"

/* You may NOT declare any global variables. */

/* You may add data members to the NgramFast class by adding them to NgramFast.h */
/* You may add more methods to the NgramFast class.  Put prototypes in NgramFast.h */
/* You may add more classes.  If you do, they need to be cleanly
 * separated into a .h and a .C files. You would add an include
 * for the .h at the top.  You would need to change the makefile
 * so that your new classes are compiled and linked with the
 * executable. */

/*
 * Ngrams
 *
 * Takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a collection
 * of ngrams. You may not use the C++ STL to define a collection object.
 * You need to implement your own. 
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList & wl)
{
   //Add any code you need to initialize whatever structure
   //you use to hold your ngrams.
   //intializes hashmap
   for (int i = 0; i < SIZE; i++)
   {
	hashMap[i] = NULL;	
   }
   //This code doesn't change
   this->ngramSz = ngramSz;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      //Insert the ngram in the collection object
      if (!ngram.empty()) insertNgram(ngram);
   }

   //You can make additional calls here if you need to.

}


/*
 * Ngrams destructor
 *
 * Automatically called when Ngrams object goes out of scope.
 * Delete any space dynamically allocated to hold the ngrams.
 */
Ngrams::~Ngrams()
{
   //pointer to current and next.
   Ngram * t_curr;
   Ngram * t_next;

   //loop throught the structure
   for (int i = 0; i < SIZE; i++)
   {
	t_curr = hashMap[i];
	//until the end of the hashmap
    while (t_curr != NULL)
	{
		//adjusts pointer 
        t_next = t_curr->next;
		//deletes node
        delete (t_curr);
		//sets current to what next points at
        t_curr = t_next;
	}
   	hashMap[i] = NULL;
   }	  
}


/*
 * insertNgram
 *
 * Inserts ngram into whatever structure you choose to hold
 * your ngrams. If the ngram is already in the collection, the
 * insert simply increments the count.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
	//intializes ptr, a new ngram node, str, and count
    Ngram * ptr = NULL;
	Ngram * newNgram = new Ngram();
	newNgram->str = s;
	newNgram->count = 1;
	int key = hash(s);
    //check if space is free
	if (hashMap[key] == NULL) { hashMap[key] = newNgram; }
	//otherwise not free space
    else
	{
		//not free
        if (find(s) == true)
		{
			//increase count of current ngram
            for (Ngram * curr = hashMap[key]; curr != NULL; curr = curr->next)
			{
				if (curr->str.compare(s) == 0) { curr->count++; }
			}
		}
		else
		{
			//moving to the next ngram
            Ngram * ptr = hashMap[key];
			//check if next exists
            while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = newNgram;
		}
	}
	//sort ngrams
    sort();	
}

void Ngrams::sort()
{
	//iterate the entire hashmap
    for (int i = 0; i < SIZE; i++)
	{
		//while hashmap hasn't reached the end
        while (hashMap[i] != NULL)
		{
			//swap if next is less than count
            for (Ngram * ptr = hashMap[i]; ptr != NULL; ptr = ptr->next)
			{
				sorted[ptr->count] = ptr;	
			}
		}
	}
}

int Ngrams::hash(std::string &sarray)
{
	//random hash value
    int x = 2917;
	int hash = 0;
    //hash function
	for (int i = 0; i < sarray.length(); i++) {
		hash = ((hash * x) + (int)sarray[i]) % SIZE;
	}
	return hash;	
}

bool Ngrams::find(std::string s)
{
	int i = hash(s);
	//loop through the hashmap until you find a match or reach the end of the map
    for (Ngram * curr = hashMap[i]; curr != NULL; curr = curr->next)
	{
		if (curr->str.compare(s) == 0)
		{
			return true;
		} 
	}
	return false;
}

/*
 * addIncreasing
 * 
 * Adds the ngrams to the ngram list in increasing order of ngram count.
 *
 */
void Ngrams::addIncreasing(NgramList * incrLst)
{
	//loop through hashmap
    for (int i = 0; i < SIZE; i++)
	{
		//until you reach a null value
        while (hashMap[i] != NULL)
		{
			//accumalate in increasing order
            for (Ngram * ptr = hashMap[i]; ptr != NULL; ptr = ptr->next)
			{
				incrLst->addToNgramList(ptr->str, ptr->count);
			}
		}
	}
       //The call to add it to the list looks something like this:
       //incrLst->addToNgramList(ngramStr, ngramCnt);
       //You will probably have this call inside of a loop (or two)
}

/*
 * addDecreasing
 *
 * Adds the ngrams to the ngram list in decreasing order of ngram count.
 *
 */
void Ngrams::addDecreasing(NgramList * decrLst)
{
	//loop through hashmap
    for (int i = SIZE - 1; i > 0; i--)
	{
		//until you reach a null value
        while (hashMap[i] != NULL)
		{
			//accumalate in decreasing order
            for (Ngram * ptr = hashMap[i]; ptr != NULL; ptr = ptr->next)
			{
				decrLst->addToNgramList(ptr->str, ptr->count);
			}
		}
	}
      //The call to add it to the list looks something like this:
      //decrLst->addToNgramList(ngramStr, ngramCnt);
      //You will probably have this call inside of a loop (or two)
}
