/*******************************************************************************
* File Name          : hashAssignment.cpp
* Description        : Implemenation of a hash skeleton
*
* Author:              PROG8130 / ???
* Date:                July 25, 2017
******************************************************************************
*/

#include "stdafx.h"
#include <windows.h>
#include <strsafe.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength);    // function to add to hash table
unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength);   // function to retrieve data from hash table

#define INPUT_BUFFER_SIZE         200             // local buffer used for adding to hash table

#define HASH_SIZE    100                          // size of hash table to be used

																				 // data structure used to keep track of hashed data
struct myHashStruct {
	char *ptrBuffer = NULL;                       // pointer to data stored in hash
	struct myHashStruct *ptrNextHashData = NULL;  // pointer to next item in this hash bucket (or NULL if no more)
};

struct myHashStruct *myHash[HASH_SIZE];             // create an empty hash table structure

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];

	// initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((myHash[i] = (struct myHashStruct *)calloc(1, sizeof(struct myHashStruct))) == NULL)
		{
			printf("calloc failed!\n");
			exit(-1);
		}
	}

	// add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// get strings from the console and place in hash until nothing entered
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
			break;

		if (putIntoHashTable(inputBuffer, strlen(inputBuffer)) == HASH_SIZE)
			printf("Error putting into hash table\n");
	}

	// check if data is in hash table
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
			break;

		if ((hashIndexNumber = getFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
	}

	return 0;
}

// FUNCTION      : myHashFunction
// DESCRIPTION   :
//   Calculate a hash value to use in storing the data into the hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//
// RETURNS       :
//   Hash value calculated ( HASH_SIZE on failure)

unsigned int myHashFunction(char *ptrInputBuffer)
{
	unsigned int calculatedHashValue = 27;

	// add code to create a hashed value here!!!

	int c; 
	while (c = *ptrInputBuffer++) {
		calculatedHashValue = ((calculatedHashValue << 5) + calculatedHashValue) + c; // calculatedHashValue * 27 + c
	}

	// make sure if hash value is bigger than the table size, the value wraps
	return calculatedHashValue % HASH_SIZE;
}

// FUNCTION      : putIntoHashTable
// DESCRIPTION   :
//   Put the supplied data into a hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//   bufferLength   - how many characters are in the buffer being put into the hash table
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrInputData);

	char word[INPUT_BUFFER_SIZE];
	int i = 0;

	strcpy_s(word, ptrInputData);

	myHashStruct *newPtr, *tempPtr;

	newPtr = (struct myHashStruct *)malloc(sizeof(struct myHashStruct));

		//Check if the data exists in pre-despositioned Hash Index.
	tempPtr = myHash[0]; //Sets this pointer at the beginning of the Hash Table.

	while (i != HASH_SIZE) {
		if (strcmp(ptrInputData, tempPtr->ptrBuffer) == 0) {
			if (tempPtr->ptrNextHashData == NULL) {
				break;
			}
			newPtr->ptrNextHashData = tempPtr->ptrNextHashData = NULL;
			return i;
		}
		else {
			i++;
		}
	}
					//Set the new data into a new Hash Index. 
	if (myHash[hashValue]->ptrBuffer == NULL) {		//Checks if the Hash Indiex contains data.
		myHash[hashValue]->ptrBuffer = ptrInputData;
		myHash[hashValue]->ptrNextHashData = NULL;
		return hashValue;
	}
	else{
		return 0;
	}
	// add code to put data into the hash table!!!

	return hashValue;
}

// FUNCTION      : getFromHashTable
// DESCRIPTION   :
//   Read as much data as there is room for from the hash table
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrOutputData);
	int i=0;
	char word[INPUT_BUFFER_SIZE];
	// check if the data is in the hash table here!!!
	while (i != HASH_SIZE) {
		if (strcmp(word, ptrOutputData)) {
			return i;
		}
		else {
			i++;
		}
	}

	return hashValue;
}

// end code *    *        