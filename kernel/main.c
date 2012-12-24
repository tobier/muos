/**
 * main.c - kernel main function
 *
 * kmain() is where we end up after the bootloader
 * has done it's work. kmain() is responsible for
 * setting up a proper GDT, interrupts, required
 * drivers et cetera.
 */
#include <muos/common.h>
#include <muos/timer.h>
#include <muos/tty.h>
#include "descriptor_tables.h"

static void announce()
{
  printk("\nMuOS - Micro Operating System\nCopyright (c) 2012, Tobias Eriksson\n");
  printk("MuOS is open source software, released under the MIT license\n\n");
}

static void enable_interrupts()
{
  asm volatile ("sti");
}

static void disable_interrupts()
{
  asm volatile ("cli");
}

void kmain(void)
{
  // Disable interrupts for now
  disable_interrupts();

  // Setup GDT, interrupts, etc.
  init_descriptor_tables();

  // Initialize drivers
  tty_init();

  // Initilize PIT at 100 Hz
  //init_timer(100);
  
  // Now it should be safe to accept interrupts
  enable_interrupts();

  // We're up and running!
  announce();
}
