#include <muos/tty.h>

static char buf[1024];

/*======================================*
 * printk
 *
 * Print a string to the screen.
 * Note: doesn't format strings at the
 * moment. 
 *======================================*/
int printk(const char *fmt, ...)
{
  char *str;
  
  for(str = buf; *fmt; ++fmt) {
    *str++ = *fmt;
  }
  *str = '\0';

  tty_write(buf, str - buf);
  return str - buf;
}

void announce()
{
  printk("\nMuOS - Micro Operating System\nCopyright (c) 2012, Tobias Eriksson\n");
  printk("MuOS is open source software, released under the MIT license");
}

void kmain(void)
{
  tty_init();

  announce();
}
