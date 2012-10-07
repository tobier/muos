#include <muos/tty.h>
#include <types.h>
#include <x86.h>

typedef struct {
  int c_column;      /* current cursor column */
  int c_row;         /* current cursor row */
  int c_size;        /* the size of the console */
  ushort c_attrib;   /* attribute used when printing characters */ 
  ushort c_blank;    /* blank character */
} console_t;

#define NUM_COLS 80
#define NUM_ROWS 25
#define CRTPORT 0x3D4
static ushort* crt = (ushort*)0xB8000;
static console_t curr_con; /* right now there is just one console */
static console_t* con = &curr_con;

static void con_clear();
static void con_setcsr(int row, int col);
static void con_memmove(ushort* src, ushort* dest, int count);
static void con_memset(ushort val, ushort* dest, int count);

/*======================================*
 * con_clear
 *
 * Clear the console.
 *======================================*/
static void con_clear()
{
  con_memset(con->c_blank, crt, con->c_size);
}

/*======================================*
 * con_setcsr
 *
 * Update the position of the cursor.
 *
 * @row The row to put the cursor on.
 * @col The column to put the cursor on.
 *======================================*/
static void con_setcsr(int row, int col)
{
  int position;
  
  /* Update the cursor. This assumes that the position is valid */
  position = row * NUM_COLS + col;
  outb(CRTPORT, 0x0E);
  outb(CRTPORT + 1, position >> 8);
  outb(CRTPORT, 0x0F);
  outb(CRTPORT + 1, position);
  crt[position++] = con->c_blank;
}

/*======================================*
 * con_memmove
 *
 * Move a section of video memory to
 * another memory location.
 *
 * @src The source video memory.
 * @dest The destination video memory.
 *======================================*/
static void con_memmove(ushort* src, ushort* dest, int count)
{
  int i;
  for(i = 0; i < count; i++) {
    *dest++ = *src++;
  }
}

/*======================================*
 * con_memset
 *
 * Set a section of video memory to the
 * given character value.
 *======================================*/
static void con_memset(ushort val, ushort* dest, int count)
{
  int i;
  for(i = 0; i < count; i++) {
    *dest++ = val;
  }
}

/*======================================*
 * con_init
 *
 * Initialize the console.
 *======================================*/
void con_init()
{
  /* Initialize the console */
  con->c_column = 0;
  con->c_row = 0;
  con->c_size = NUM_ROWS * NUM_COLS;
  con->c_attrib = 0x0700;      /* that's white on black */
  con->c_blank = ' ' | 0x0700; /* blank with black background */

  con_clear();
  con_setcsr(0, 0);
}

/*======================================*
 * con_putc
 *
 * Print a character to the console.
 *======================================*/
void con_putc(char c)
{
  switch(c) {
  case '\n':
    con->c_column = 0;
    con->c_row++;
    break;
  case '\b':
    if(con->c_column > 0) con->c_column--;
    break;
  default:
    crt[con->c_row * NUM_COLS + con->c_column++] = (c & 0xFF) | con->c_attrib;
    if(con->c_column >= NUM_COLS) {
      con->c_column = 0;
      con->c_row++;
    }
    break;
  }

  /* Scroll if neccessary */
  if(con->c_row >= NUM_ROWS) {
    con_memmove(crt + NUM_COLS, crt, (NUM_ROWS - 1) * NUM_COLS);
    con_memset(con->c_blank, crt + (NUM_ROWS - 1) * NUM_COLS, NUM_COLS);
    con->c_row = NUM_ROWS - 1;
  }

  con_setcsr(con->c_row, con->c_column);
}
