#include <stdio.h>
#include <stdint.h>
#include "murmur3.h"


const int BUCKET_HEIGHT = 2;    // ### need to change this
const int SUBTABLE_SIZE = 5;
const int TABLE_SIZE = 13;
const uint32_t SEED = 42;


struct Bucket
{
	int counter = 0;                // keep count of filled cells
	uint32_t fingerprint[BUCKET_HEIGHT];
};

struct SubTable
{
	struct bucket buckets[SUBTABLE_SIZE];   /* bucket array*/
};

struct Table
{
	struct SubTable subtables[TABLE_SIZE];      /* subtables array, bucket count, subtables count */
};


*Table New() {
	struct Table T1;   // it will return the pointer to the table
	return &T1;
}

//Get the index number by hash and get the bucket from that subtables.
Bucket* getTargets(*uint32_t key, *Table td) {
	struct Bucket *bucketRef[TABLE_SIZE];
	uint32_t out;
	for (int i = 0; i < TABLE_SIZE; i++) {
		MurmurHash3_x86_32(*key, SEED, out);					//calculate the hash value for each subtables,
		if (td->subtables[i].buckets[out % SUBTABLE_SIZE].counter == BUCKET_HEIGHT) {
			bucketRef[i] = NULL;
			continue;
		}
		bucketRef[i] = &(td->subtables[i].buckets[out % SUBTABLE_SIZE]);   		// Then divide hash value by subtable size
	}
	return bucketRef;
}

bool inserting(*uint32_t key, *Table td) {
	struct Bucket *bucketList[TABLE_SIZE] = getTargets(key, td);
	bool emptyArr = checkEmptyArray(bucketList);
	if (emptyArr) {
		int minCount = BUCKET_HEIGHT, index = 0;
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (bucketList[i] != NULL) {
				if (minCount > bucketList[i]->counter) {
					minCount = bucketList[i]->counter;
					index = i;
				}
			}
		}
		bucketList[index]->fingerprint[minCount] = *key;
		bucketList[i]->counter = bucketList[i]->counter + 1;
	} else {
		fmt.printf("[Error]:Key already exists\n");
		return false;
	}
	return true;
}

//Check if no room in any bucket
void checkEmptyArray(*Bucket bucketList) {
	bool emptyArr = false;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (bucketList[i] != NULL) {
			emptyArr = true;
			break;
		}
	}
	return emptyArr
}
