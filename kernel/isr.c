/**
 * isr.c - High level interrupt service routines and interrupt request handlers.
 */
#include <muos/common.h>
#include <muos/tty.h>
#include <asm.h>
#include <isr.h>

void isr_handler(registers_t regs)
{
  printk("Unhandled interrupt: %d, error: %d\n", regs.int_no, regs.err_code);
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void irq_handler(registers_t regs)
{
  /* Send an EOI (end of interrupt) signal to the PICs. */
  if(regs.int_no >= 40) {
    outb(PIC2_COMMAND, 0x20);
  }
  outb(PIC1_COMMAND, 0x20);
  
  if(interrupt_handlers[regs.int_no] != 0) {
    isr_t handler = interrupt_handlers[regs.int_no];
    handler(regs);
  }
}
