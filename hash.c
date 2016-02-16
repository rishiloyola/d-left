#include <stdio.h>
#include <stdint.h>
#include "murmur3.h"
#include <stdbool.h>


const int BUCKET_HEIGHT = 2;    // ### need to change this
const int SUBTABLE_SIZE = 5;
const int TABLE_SIZE = 13;
const uint32_t SEED = 42;


struct Bucket
{
	int counter;                // keep count of filled cells
	uint32_t fingerprint[BUCKET_HEIGHT];
};

struct SubTable
{
	struct Bucket buckets[SUBTABLE_SIZE];   /* bucket array*/
};

struct Table
{
	struct SubTable subtables[TABLE_SIZE];      /* subtables array, bucket count, subtables count */
};


// struct Table *New() {
// 	struct Table T1;   // it will return the pointer to the table
// 	return &T1;
// }

//Get the index number by hash and get the bucket from that subtables.
// struct Bucket * getTargets(uint32_t key, struct Table *td) {
// 	static struct Bucket *bucketRef[TABLE_SIZE];
// 	uint32_t out;
// 	for (int i = 0; i < TABLE_SIZE; i++) {
// 		MurmurHash3_x86_32((const void *)&key, sizeof(uint32_t), SEED, &out);					//calculate the hash value for each subtables,
// 		if (td->subtables[i].buckets[out % SUBTABLE_SIZE].counter == BUCKET_HEIGHT) {
// 			bucketRef[i] = NULL;
// 			continue;
// 		}
// 		bucketRef[i] = &(td->subtables[i].buckets[out % SUBTABLE_SIZE]);   		// Then divide hash value by subtable size
// 	}
// 	return bucketRef;
// }
int * getTargets(uint32_t key, struct Table *td) {
	static int bucketID[TABLE_SIZE];
	uint32_t out;
	for (int i = 0; i < TABLE_SIZE; i++) {
		MurmurHash3_x86_32((const void *)&key, sizeof(uint32_t), SEED, &out);					//calculate the hash value for each subtables,
		if (td->subtables[i].buckets[out % SUBTABLE_SIZE].counter == BUCKET_HEIGHT) {
			bucketID[i] = -1;
			continue;
		}
		bucketID[i] = out % SUBTABLE_SIZE;   		// Then divide hash value by subtable size
	}
	return bucketID;
}

//Check if no room in any bucket   ####check the getting array
bool checkEmptyArray(int *bucketList) {
	bool emptyArr = false;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (bucketList[i] != -1) {
			emptyArr = true;
			break;
		}
	}
	return emptyArr;
}

bool inserting(uint32_t key, struct Table *td) {
	int *bucketList = getTargets(key, td);
	bool emptyArr = checkEmptyArray(bucketList);
	if (emptyArr) {
		int minCount = BUCKET_HEIGHT, index = 0;
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (bucketList[i] != -1) {
				if (minCount > td->subtables[i].buckets[bucketList[i]].counter) {
					minCount = td->subtables[i].buckets[bucketList[i]].counter;
					index = i;
				}
			}
		}
		td->subtables[index].buckets[bucketList[index]].fingerprint[minCount] = key;
		td->subtables[index].buckets[bucketList[index]].counter += 1;
	} else {
		printf("[Error]:Key already exists\n");
		return false;
	}
	return true;
}
