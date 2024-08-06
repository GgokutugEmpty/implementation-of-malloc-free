//MAIN.C
//Author : A.Goktug
#include "HEAD.H"
int main()
 {
    print_memory_status("Before any allocation:");

    void *ptr1 = malloc(100);
    print_memory_status("After malloc(100):");

    void *ptr2 = malloc(200);
    print_memory_status("After malloc(200):");

    free(ptr1);
    print_memory_status("After free(ptr1):");

    void *ptr3 = malloc(50);
    print_memory_status("After malloc(50):");

    free(ptr2);
    print_memory_status("After free(ptr2):");

    free(ptr3);
    print_memory_status("After free(ptr3):");

    return 0;
}