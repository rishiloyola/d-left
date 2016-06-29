#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "murmur3.h"


const int BUCKET_HEIGHT = 2;    // ### need to change this
const int SUBTABLE_SIZE = 5;
const int TABLE_SIZE = 13;
const uint32_t SEED = 42;


struct Bucket
{
	int counter;              // keep count of filled cells
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


int * getTargets(uint32_t key, struct Table *td)
{
	static int bucketID[TABLE_SIZE];
	uint32_t out;
	MurmurHash3_x86_32((const void *)&key, sizeof(uint32_t), SEED, &out);					//calculate the hash value for each subtables,
	int position = out % SUBTABLE_SIZE;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (td->subtables[i].buckets[position].counter == BUCKET_HEIGHT) {
			bucketID[i] = -1;
		} else {
			bucketID[i] = position;   		// Then divide hash value by subtable size
		}
	}
	return bucketID;
}


//Check if no room in any bucket
bool checkEmptyArray(int *bucketList)
{
	bool emptyArr = false;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (bucketList[i] != -1) {
			emptyArr = true;
			break;
		}
	}
	return emptyArr;
}


bool inserting(uint32_t key, struct Table *td)
{
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
		if (minCount != BUCKET_HEIGHT) {
			td->subtables[index].buckets[bucketList[index]].fingerprint[minCount] = key;
			td->subtables[index].buckets[bucketList[index]].counter += 1;
			printf("Key is inserted successfully - %d\n", key);
		} else {
			printf("[Error]:Key cannot inserted\n");
		}
	} else {
		printf("[Error]:Key already exists\n");
		return false;
	}
	return true;
}


int * getBuckets(uint32_t key, struct Table *td)
{
	static int bucketID[TABLE_SIZE];
	uint32_t out;
	MurmurHash3_x86_32((const void *)&key, sizeof(uint32_t), SEED, &out);					//calculate the hash value for each subtables,
	int position = out % SUBTABLE_SIZE;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (td->subtables[i].buckets[position].counter == 0) {
			bucketID[i] = -1;
		} else {
			bucketID[i] = position;   		// Then divide hash value by subtable size
		}
	}
	return bucketID;
}


bool lookup(uint32_t key, struct Table *td)
{
	int *bucketList = getBuckets(key, td);
	bool emptyArr = checkEmptyArray(bucketList);
	if (emptyArr) {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (bucketList[i] != -1) {
				for (int j = 0; j < BUCKET_HEIGHT; j++) {
					if (td->subtables[i].buckets[bucketList[i]].fingerprint[j] == key) {
						return true;
					}
				}
			}
		}
	} else {
		printf("[Error]: Key does not exists\n");
		return false;
	}
	return false;
}


bool delete(uint32_t key, struct Table *td)
{
	int *bucketList = getBuckets(key, td);
	bool emptyArr = checkEmptyArray(bucketList);
	bool deleted = false;
	if (emptyArr) {
		int bucketIndex, cellIndex;
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (bucketList[i] != -1) {
				for (int j = 0; j < BUCKET_HEIGHT; j++) {
					if (td->subtables[i].buckets[bucketList[i]].fingerprint[j] == key) {
						bucketIndex = i;
						cellIndex = j;
						deleted = true;
						break;
					}
				}
			}
		}
		if (deleted) {
			for (int i = cellIndex; i < BUCKET_HEIGHT; i++) {
				td->subtables[bucketIndex].buckets[bucketList[bucketIndex]].fingerprint[i] = td->subtables[bucketIndex].buckets[bucketList[bucketIndex]].fingerprint[i + 1];
			}
			td->subtables[bucketIndex].buckets[bucketList[bucketIndex]].counter -= 1;
			printf("The key %d is deleted successfully\n ", key);
			return true;
		} else {
			printf("[Error]: Key does not exists\n");
			return false;
		}
	} else {
		printf("[Error]: Key does not exists\n");
		return false;
	}
	return false;
}

void init(struct Table *td) 
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		for (int j = 0; j < SUBTABLE_SIZE; j++) {
			td->subtables[i].buckets[j].counter = 0;
		}
	}
}
