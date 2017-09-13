#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

void *alloc_exec_mem(size_t sz) {
        void *exec_buf = mmap(0, sz, PROT_READ | PROT_WRITE | PROT_EXEC, 
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);  
    if ((long int)exec_buf == -1) {
        return NULL;
    }
    return exec_buf;
}

#define CODE_SIZE 255

int main(int ac, char *av[]) {
                                                  //  int foo(int a) {
                                                  //      return ++a;
                                                  //  }
    char code[CODE_SIZE] = { 
                           0x55,                  // push   %rbp
                           0x48, 0x89, 0xe5,      // mov    %rsp,%rbp
                           0x89, 0x7d, 0xfc,      // mov    %edi,-0x4(%rbp)
                           0x83, 0x45, 0xfc, 0x01,// addl   $0x1,-0x4(%rbp)
                           0x8b, 0x45, 0xfc,      // mov    -0x4(%rbp),%eax
                           //0x5d,                  // pop    %rbp
                           0x0f, 0x24,            // PROBABLY THAT SHOULD BE UD
                           0xc3};                 // retq   


    void *m = alloc_exec_mem(CODE_SIZE);
    if (!m) return 0;

    memcpy(m, code, CODE_SIZE);

    int (*p_f)(int) = m;

    printf("Foo %d\n", p_f(3));
    return 1;
}

