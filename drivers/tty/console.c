/* 
   tty/console.c
   This part of the tty driver is responsible for 
   writing to the screen. 
*/
#include <types.h>
#include <x86.h>

/* Text mode supports 80x25 characters */
#define COLS 80
#define ROWS 25

/* 
   Each text mode character takes up 2 bytes. 
   The least significant byte is the ASCII character,
   the most significant byte is the foreground and background colors.
*/
static ushort* videoram = (ushort*)0xB8000;

#define CRTPORT 0x3D4

static void
cons_putc(int c)
{
  int position;
  
  /* Read the current cursor position */
  outb(CRTPORT, 0x0E);
  position = inb(CRTPORT + 1) << 8;
  outb(CRTPORT, 0x0F);
  position |= inb(CRTPORT + 1);

  /* Handle newline */
  if(c == '\n')
    position += 80 - position % 80;
  else if(c == '\b' && position > 0)
    position--;
  else
    videoram[position++] = (c & 0xFF) | 0x0700;

  /* Reset the cursor */
  outb(CRTPORT, 0x0E);
  outb(CRTPORT + 1, position >> 8);
  outb(CRTPORT, 0x0F);
  outb(CRTPORT + 1, position);
  videoram[position++] = ' ' | 0x0700;
}

void
cons_init(void)
{
  /* Clear the console by printing a space
     that has a black background color in
     each position */
  int pos;
  for(pos = 0; pos < ROWS*COLS; pos++)
    videoram[pos] = ' ' | 0x0700;

  /* Reset the cursor */
  outb(CRTPORT, 0x0E);
  outb(CRTPORT + 1, 0);
  outb(CRTPORT, 0x0F);
  outb(CRTPORT + 1, 0);

  cons_putc('H');
  cons_putc('e');
  cons_putc('l');
  cons_putc('l');
  cons_putc('o');
  cons_putc('!');
}
