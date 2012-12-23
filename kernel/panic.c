/**
 * panic.c - kernel panic
 *
 * A kernel panic is usually triggered by using
 * the PANIC-macro as defined in muos/common.h.
 * The result of a kernel panic is to print a convenient
 * error message, and then hanging the kernel.
 */
#include <muos/common.h>

void panic(const char *message, const char *file, uint32_t line)
{
  printk("kernel panic: %s, in file %s:%d", message, file, line);
  
  for(;;); // hang
}
