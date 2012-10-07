#ifndef _TTY_H_
#define _TTY_H_

#include <types.h>

void tty_init(void);
int tty_write(char *buf, uint count);

#endif
