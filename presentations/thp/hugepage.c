#include<sys/mman.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<inttypes.h>

#define NUM_PAGES 10

int main(){
	int i, p, page_size;

	page_size = sysconf(_SC_PAGE_SIZE);
	uint64_t huge_page_size = page_size<<9;

	// Allocating 2MB huge pages in libhugetlbfs using the MAP_HUGETLB flag
	char* buffer = (char*) mmap (NULL, NUM_PAGES * huge_page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_HUGETLB , -1, 0);
	if(buffer == (void *) -1){
		printf("Cannot allocate hugepage. Check /sys/kernel/mm/hugepage for number of hugepages available\n");
		exit(0);
	}

	// Writing to the huge page (because pages are allocated on demand)
	char *temp, *stop_cmd;
	for(p=0; p < NUM_PAGES; p++){
		temp = buffer + (p*huge_page_size);
		*(temp) = 'a';
	}

	// Wait forever
	while (1) {
		printf("sleeping\n");
		sleep(2);
	}
}
