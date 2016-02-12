#include <stdio.h>
#include <stdint.h>

const int bucketHeight = 10;    // ### need to change this
const int subTableSize = 20;
const int tableSize = 5;

struct fingerprint
{
	uint32_t key;               // 32 bit key
};

struct bucket
{
	int counter;                // keep count of filled cells
	struct fingerprint cells[bucketHeight];      // cells per bucket
};

struct subTable
{
	struct bucket buckets[subTableSize];   /* bucket array*/
};

struct Table
{
	struct subTable subtables[tableSize];      /* subtables array, bucket count, subtables count */
};


void New(){
	// This is the function to initialize the variables.
	// it will return the pointer to the table
}
