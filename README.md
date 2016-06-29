# d-left

### Run
```
gcc -o murmur3 murmur3.c
gcc -o hash hash.c murmur3.o
./hash
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
Change the below parameter to generate the hash table of suitable size.
```c
const int BUCKET_HEIGHT = 2;
const int SUBTABLE_SIZE = 5;
const int TABLE_SIZE = 13;
const uint32_t SEED = 42;
```
##### Note: 
* Currently it only supports **uint32_t** data type.
