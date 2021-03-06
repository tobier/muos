#include <muos/tty.h>

void kbd_init();
void con_init();
void con_putc(char c);

/*======================================*
 * tty_init
 *
 * Initialize the tty driver
 *======================================*/
void tty_init(void)
{
  con_init();
  kbd_init();
}

/*======================================*
 * tty_write
 *
 * Write to the tty device from the given
 * buffer. 
 *
 * @buf Character buffer to write from.
 * @count How many characters to write.
 *
 * @returns How many characters that were
 *          actually written.
 *======================================*/
int tty_write(char *buf, uint32_t count)
{
  // the tty device should have some sort of
  // write queue, but right now we just print
  // the characters in 'buf'.
  char c, *b = buf;

  while(count--) {
    c = *b++;
    con_putc(c);
  }

  return b - buf;
}
