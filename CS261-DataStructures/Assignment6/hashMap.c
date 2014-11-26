#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
	{
		return;
	}

	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
	{
		ht->table[index] = NULL;
	}
}

/*
Purpose: Gets the hash number from the hash function.
		 This function determines which hash function
		 to use depending on the definition of HASHING_FUNCTION
		 located in the hashMap.h file
Preconditions: n/a
Parameters: str - a null terminated string to hashify
Returns: a hash number
*/
int _getIndexFromHashFunc(char *str)
{
	if (HASHING_FUNCTION == 1)
	{
		// Use the first hashing function
		return stringHash1(str);
	}
	else
	{
		// Use the second hashing function
		return stringHash2(str);
	}
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	/*FIXME*/
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
Preconditions: 1. hash table is not null
			   2. new table size is greater than 0
Parameters: ht
Returns: n/a
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*FIXME*/
	// Check Preconditions
	assert(ht != 0);
	assert(newTableSize > 0);
}

/*
 Implementation Notes:
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided, replace the value of that
 hashLink with the new value and exit the function.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).

Purpose:
Preconditions: n/a
Parameters: ht -
			k -
			v -
Returns: n/a
*/
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	/*FIXME*/
	// Check Preconditions
	assert(ht != 0);

	if ((ht->count / (double)ht->tableSize) > LOAD_FACTOR_THRESHOLD)
	{
		// Add code to set table size to a new prime number
	}

	// Get hash index based on the key
	int index = _getIndexFromHashFunc(k) % ht->tableSize;
	if (index < 0)
	{
		index += ht->tableSize;
	}

	// Check if hash link exists, if it does then replace the link
	if (containsKey(ht, k) == 1)
	{
		/*FIXME*/
		struct hashLink *curPtr = ht->table[index];
		while(curPtr != 0)
		{
			if (curPtr->key == k)
			{
				// Found the key, set the value for the current hash link
				curPtr->value = v;
				return;
			}

			curPtr = curPtr->next;
		}
	}

	// if hash link does not exist,
	struct hashLink *newLink = malloc(sizeof(struct hashLink));
	newLink->key = k;
	newLink->value = v;
	newLink->next = ht->table[index];
	ht->table[index] = newLink;
	ht->count++;
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	/*FIXME*/
	return NULL;
}

/*
Purpose: Checks if a key is in a hash table
Preconditions: Hash map is not null
Parameters: ht - pointer to a hash map
			k - the key to search for
Returns: Returns 1, if key is in hash table
		 Returns 0, if key is not in hash table
*/
int containsKey (struct hashMap * ht, KeyType k)
{  
	// Check Preconditions
	assert(ht != 0);

	// Get hash index based on the key
	int index = _getIndexFromHashFunc(k) % ht->tableSize;
	if (index < 0)
	{
		index += ht->tableSize;
	}

	struct hashLink *curPtr = ht->table[index];
	while(curPtr != 0)
	{
		if (curPtr->key == k)
		{
			return 1;
		}

		curPtr = curPtr->next;
	}

	return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	/*FIXME*/
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*FIXME*/
	return 0;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*FIXME*/
	return 0;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*FIXME*/
	return 0;
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


