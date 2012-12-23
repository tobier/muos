#ifndef _DESC_TABLES_H_
#define _DESC_TABLES_H_

#include <types.h>

/* This structure contains the value of one GDT entry */
struct gdt_entry_struct {
  uint16_t limit_low;        // The lower 16 bits of the limit.
  uint16_t base_low;         // The lower 16 bits of the base.
  uint8_t base_middle;       // The next 8 bits of the base.
  uint8_t access;            // Access flags, determine what ring this segment can be used in.
  uint8_t granularity;
  uint8_t base_high;         // The last 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

/* A struct describing an interrupt gate. */
struct idt_entry_struct
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

/* These are the 32 CPU-dedicated interrupt handlers */
extern void isr0();    /* Division by zero exception */
extern void isr1();    /* Debug exception */
extern void isr2();    /* Non-maskable interrupt */
extern void isr3();    /* Breakpoint exception */
extern void isr4();    /* Into detected overflow */
extern void isr5();    /* Out of bounds exception */
extern void isr6();    /* Invalid opcode exception */
extern void isr7();    /* No processor exception */
extern void isr8();    /* Double fault (pushes error code) */
extern void isr9();    /* Coprocessor segment overrun */
extern void isr10();   /* Bad TSS (pushed error code) */
extern void isr11();   /* Segment not present (pushes error code) */
extern void isr12();   /* Stack fault (pushes error code) */
extern void isr13();   /* General protection fault (pushes error code) */
extern void isr14();   /* Page fault (pushes error code) */
extern void isr15();   /* Unknown interrupt exception */
extern void isr16();   /* Coprocessor fault */
extern void isr17();   /* Alignment check exception */
extern void isr18();   /* Machine check exception */
extern void isr19();   /* Reserved */
extern void isr20();   /* Reserved */
extern void isr21();   /* Reserved */
extern void isr22();   /* Reserved */
extern void isr23();   /* Reserved */
extern void isr24();   /* Reserved */
extern void isr25();   /* Reserved */
extern void isr26();   /* Reserved */
extern void isr27();   /* Reserved */
extern void isr28();   /* Reserved */
extern void isr29();   /* Reserved */
extern void isr30();   /* Reserved */
extern void isr31();   /* Reserved */

/* The kernel should call this to setup the descriptor tables */
void init_descriptor_tables();

#endif/*_DESC_TABLES_H_*/
