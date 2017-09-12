#include <stdio.h>
#include <sys/mman.h>
#include <string.h>


int foo(int a) {
	return ++a;
}

int bar(int a) {
        return a--;
}

void *alloc_exec_mem(size_t sz) {
        void *exec_buf = mmap(0, sz, PROT_READ | PROT_WRITE | PROT_EXEC, 
	    	              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);	
	if ((long int)exec_buf == -1) {
		return NULL;
	}
	return exec_buf;
}


int main(int ac, char *av[]) {
	long int foo_size = (long int)bar-(long int)foo;
	printf("Size foo %ld\n", foo_size);

	void *m = alloc_exec_mem(foo_size);
	if (!m) return 0;

	memcpy(m, &foo, foo_size);

	int (*p_f)(int) = m;


	printf("Foo %d\n", p_f(3));
	return 1;
}

