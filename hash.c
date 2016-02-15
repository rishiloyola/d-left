#include <stdio.h>
#include <stdint.h>
#include "murmur3.h"


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
Bucket* getTargets(uint32_t key, *Table td) {
	struct Bucket *bucketRef[TABLE_SIZE];
	uint32_t out;
	for (int i = 0; i < sizeof(td.SubTable) / sizeof(td.SubTable[0]); i++) {
		MurmurHash3_x86_32(key, SEED, out);					//calculate the hash value for each subtables,
		bucketRef[i] = &(td.subtables[i].buckets[out % SUBTABLE_SIZE]);   		// Then divide hash value by subtable size
	}
	return bucketRef;
}

void Add() {

}
