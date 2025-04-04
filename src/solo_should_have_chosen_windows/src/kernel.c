#include "gdt/gdt_function.h"
#include "terminal/print.h"
#include "interrupts/idt_function.h"

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"

#include <multiboot2.h>



struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    gdt_init();
    printf("gdt now loaded\n");

    idt_init();
    printf("idt now loaded\n");
    
    enable_interrupts();
    printf("interrupts enabled\n");
    
       // Keep the CPU running forever
    while (1) {
        __asm__ volatile ("hlt");
    }
    
    return 0;

}