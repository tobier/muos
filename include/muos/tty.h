/**
 * tty.h - terminal driver
 *
 * The tty driver is responsible for console output,
 * and is used by calling printk() (see muos/common.h) 
 * rather than calling tty_write() directly.
 * kmain() is responsible for calling tty_init() before
 * the tty driver is used.
 */
#ifndef _TTY_H_
#define _TTY_H_

#include <types.h>

void tty_init(void);
int tty_write(char *buf, uint32_t count);

#endif
