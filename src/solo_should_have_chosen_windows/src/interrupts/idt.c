#include "interrupts/idt_structs.h"
#include "interrupts/idt_function.h"
#include "terminal/print.h"

#define IDT_ENTRIES 256

static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t idt_ptr;

// Function to set an IDT entry
void set_idt_entry(int index, uint32_t isr_function, uint16_t selector, uint8_t type_attr) {
    idt[index].offset_low = isr_function & 0xFFFF;          
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attr = type_attr;
    idt[index].offset_high = (isr_function >> 16) & 0xFFFF;
}

// Generic ISR function
void isr_stub() {
    printf("An undefined ISR was fired\n");
}

// Test ISR functions
void isr20() {
    printf("Interrupt 0x20 fired\n");
}

void isr21() {
    printf("Interrupt 0x21 fired\n");
}

void isr22() {
    printf("Interrupt 0x22 fired\n");
}

void idt_init() {
    // Define the IDT by using the pointer
    idt_ptr.limit = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < 256; ++i) {
        set_idt_entry(i, (uint32_t)isr_stub, 0x08, 0x8E);
    }

    set_idt_entry(0x20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_entry(0x21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_entry(0x22, (uint32_t)isr22, 0x08, 0x8E);

    // Load the IDT
    __asm__ volatile ("lidt %0" : : "m" (idt_ptr));
}