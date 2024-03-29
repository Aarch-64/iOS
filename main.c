// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "vga.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "multiboot.h"
#include "fs.h"
#include "initrd.h"
#include "task.h"
#include "syscall.h"

extern u32int placement_address;
u32int initial_esp;

void start_kernel(struct multiboot *mboot_ptr, u32int initial_stack)
{
    initial_esp = initial_stack;
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();

    // Initialise the PIT to 100Hz
    asm volatile("sti");
    init_timer(50);

    // Find the location of our initial ramdisk.
    ASSERT(mboot_ptr->mods_count > 0);
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;

    //Initialise paging with the memory amount reported by GRUB
    u32int memsz = ((mboot_ptr->mem_lower + mboot_ptr->mem_upper) * 1024); //Bytes
    init_paging(memsz);
    printk("Paging initialised with %dMB of memory...\n",(memsz/1024/1024));

    u32int malloc_test = kmalloc(100);
    if(malloc_test != 0)
    {
         printk("MMU working as expected:\n\tMemory test assigned 100 bytes at 0x%x...\n",malloc_test);
         kfree((void*)malloc_test);
    }
    else
    	printk("MMU failed test...\n");

    fs_root = initialise_initrd(initrd_location);
    printk("RAMFS initialised...\n");
    
    // Start multitasking.
    initialise_tasking();
    
    initialise_syscalls();

    switch_to_user_mode();

    syscall_print("Hello, user world!\n");
}
