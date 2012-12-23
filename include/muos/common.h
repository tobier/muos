/**
 * common.h - Commonly used functions
 *
 * There are a couple of functions that are
 * commonly used throughout the entire kernel
 * (including drivers), and they're declared here.
 */
#ifndef _COMMON_H_
#define _COMMON_H_

#include <types.h>

int printk(const char *fmt, ...);

// Very useful macro for kernel panics!
// Thanks to JamesM's kernel development tutorials for this!
#define PANIC(msg) panic(msg, __FILE__, __LINE__);
void panic(const char *message, const char *file, uint32_t line);

#endif/*_COMMON_H_*/
