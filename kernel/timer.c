#include <muos/common.h>
#include <muos/timer.h>
#include <asm.h>
#include <isr.h>

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
  tick++;
  printk("interrupt %d, tick: %d\n", regs.int_no, tick);
}

void init_timer(uint32_t frequency)
{
  // Firstly, register our timer callback.
  register_interrupt_handler(IRQ0, &timer_callback);

  uint32_t divisor = 1193180 / frequency;       /* Calculate our divisor */

  outb(0x43, 0x36);             /* Set our command byte 0x36 */
  outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
  outb(0x40, divisor >> 8);     /* Set high byte of divisor */
}
