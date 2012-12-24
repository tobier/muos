#ifndef _ASM_H_
#define _ASM_H_

static inline uint8_t
inb(uint16_t port)
{
  uint8_t data;

  asm volatile("in %1,%0" : "=a" (data) : "d" (port));
  return data;
}

static inline void
outb(uint16_t port, uint8_t data)
{
  asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#endif/*_ASM_H_*/
