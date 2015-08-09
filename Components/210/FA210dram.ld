/*
 *  Linker script, fa s5pv210 board, DRAM0 512MB
 */
 
 ENTRY(start) 

 MEMORY
   {
      dram0(wx) : ORIGIN = 0x20000000, LENGTH = 512M
   }
 SECTIONS
   {
    .start : 
    {
        *(.start)
    }
   }
   
   
   