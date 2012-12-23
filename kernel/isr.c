/**
 * isr.c - High level interrupt service routines and interrupt request handlers.
 */

#include <muos/common.h>
#include <muos/tty.h>

typedef struct registers
{
  uint32_t ds;                                     /* Data segment selector */
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
  uint32_t int_no, err_code;                       /* Interrupt number and error code (if applicable) */
  uint32_t eip, cs, eflags, useresp, ss;           /* Pushed by the processor automatically. */
} registers_t;

void isr_handler(registers_t regs)
{
  printk("Unhandled interrupt: %d, error: %d\n", regs.int_no, regs.err_code);
}
