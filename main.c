int
main(void)
{
  /* Print a letter to screen to see everything is working: */
   unsigned char *videoram = (unsigned char *)0xB8000;
   videoram[0] = 65; /* character 'A' */
   videoram[1] = 0x07; /* light grey (7) on black (0). */

   for(;;)
     ;

   /* should never be reached */
   return 0;
}
