#include <stdio.h>
#include <stdint.h>

const int bucketHeight = 10;    // ### need to change this

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
	/* bucket array*/
};

struct Table
{
	/* subtables array, bucket count, subtables count */
};