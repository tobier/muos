/**
 * main.c - kernel main function
 *
 * kmain() is where we end up after the bootloader
 * has done it's work. kmain() is responsible for
 * setting up a proper GDT, interrupts, required
 * drivers et cetera.
 */
#include <muos/common.h>
#include <muos/tty.h>

static void announce()
{
  printk("\nMuOS - Micro Operating System\nCopyright (c) 2012, Tobias Eriksson\n");
  printk("MuOS is open source software, released under the MIT license\n\n");
}

void kmain(void)
{
  // Setup GDT, interrupts, etc.
  // ...

  // Initialize drivers
  tty_init();

  // We're up and running!
  announce();

  printk("testing a string: %s\n", "foobar");
  printk("testing an int: %d\n", 2439);
  printk("testing both: %s, %d\n", "foobar", 941232);
  printk("testing a hexadecimal int: %p\n", 0xA12F);

  PANIC("kernel has nothing to do");
}
