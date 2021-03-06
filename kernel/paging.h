extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int first_page_table[1024] __attribute__((aligned(4096)));


void pagetable_init(){
        // holds the physical address where we want to start mapping these pages to.
        // in this case, we want to map these pages to the very beginning of memory.
        unsigned int i;
 
        //we will fill all 1024 entries in the table, mapping 4 megabytes
        for(i = 0; i < 1024; i++){
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
                first_page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
        }
}

void pagedir_init(){
	//set each entry to not present
	//write_string("Create page direcory");
	int i;
	for(i = 0; i < 1024; i++){
    // This sets the following flags to the pages:
    //   Supervisor: Only kernel-mode can access them
    //   Write Enabled: It can be both read from and written to
    //   Not Present: The page table is not present
	    page_directory[i] = 0x00000002;
	}

	// attributes: supervisor level, read/write, present
	page_directory[0] = ((unsigned int)first_page_table) | 3;
}

void paging_init(){
	write_string("Paging init");
	pagetable_init();
	pagedir_init();

	loadPageDirectory(page_directory);
	enablePaging();
}

