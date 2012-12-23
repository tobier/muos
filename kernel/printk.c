#include <muos/common.h>
#include <muos/tty.h>
#include <stdarg.h>
#include <string.h>

// printk buffer
static char buf[1024];
// these are the digits we use then printing
static char* digits = "0123456789ABCDEF";

static char* itoa(char *sp, uint32_t number, int base)
{
  char tmp[16]; 
  char *tp = tmp;
  int i;
  
  while (number || tp == tmp) {
    i = number % base;
    number /= base;
    *tp++ = digits[i];
  }
  
  if( base == 16 ) {
    *tp++ = 'x';
    *tp++ = '0';
  }

  while (tp > tmp) {
    *sp++ = *--tp;
  }
  
  return sp;
}

static int vsprintf(char *buffer, const char *fmt, va_list args)
{
  char *str, *s;
  int i, len;

  for(str = buffer; *fmt; ++fmt) {

    if(*fmt != '%') {
      *str++ = *fmt;
      continue;
    }

    /* skip the '%' */
    ++fmt;
    
    switch(*fmt) {
    case 's':
      s = va_arg(args, char*);
      len = strlen(s);
      for(i = 0; i < len; ++i) {
	*str++ = *s++;
      }
      break;
    case 'd':
      str = itoa(str, va_arg(args, uint32_t), 10);
      break;
    case 'p':
      str = itoa(str, va_arg(args, uint32_t), 16);
      break;
    default: /* unhandled, print the unformatted text */
      *str++ = '%';
      *str++ = *fmt;
    }
  }

  return str - buffer;
}

/**
 * printk - print to the terminal
 *
 * Only understands %d, %s, %p, prints everything
 * else as unformatted text.
 */
int printk(const char *fmt, ...)
{
  va_list args;
  uint32_t nbytes;

  va_start(args, fmt);
  nbytes = vsprintf(buf, fmt, args);
  va_end(args);
  
  tty_write(buf, nbytes);
  return nbytes;
}
