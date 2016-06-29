# d-left
A d-left is a data structure designed to store data, rapidly, memory-efficiently and with very less collision probability compare to Bloom Filter. Check out this [experiment](https://www.eecs.harvard.edu/~michaelm/postscripts/aller2006.pdf) to increase the capacity and to reduce the false positive of Bloom Filter.

### Advantages :
* Separation of data and use of fingerprints allows checking of several locations per memory access.
* Multiple hash functions significatly reduces collision probability.
* Number of memory accesses rarely exceeds d+1.

### Run
```
gcc -c murmur3.c hash.c main.c
gcc -o test murmur3.o hash.o main.o
./test
```

### Dependency
[Murmur3 hashing](https://github.com/PeterScott/murmur3)

### Refereces
1. [Algorithms - ESA 2006](https://books.google.co.in/books?id=eKOoCAAAQBAJ&pg=PA688&lpg=PA688&dq=d-left+deletion+hashing&source=bl&ots=_t4AgfeEqs&sig=6pc27jDRL5SybempvGOaUr62jlE&hl=en&sa=X&redir_esc=y#v=onepage&q=d-left%20hashing&f=false)
2. [Slide](http://www.arl.wustl.edu/~jst/cse/577/lec/exactMatch.pdf)


### Usage
```c
int main(int argc, char const *argv[])
{
	struct Table T1;
	init(&T1);
	bool output;
	for (int i = 0; i < 10; i++) {
		output = inserting(i, &T1);
	}
	output = delete(5, &T1);
	output = delete(1, &T1);
	output = lookup(5, &T1);
	return 0;
}
```

### Config
Change the below parameters to generate the hash table of suitable size.
```c
const int BUCKET_HEIGHT = 2;
const int SUBTABLE_SIZE = 5;
const int TABLE_SIZE = 13;
const uint32_t SEED = 42;
```
##### Note: 
* Currently it only supports **uint32_t** data type.
