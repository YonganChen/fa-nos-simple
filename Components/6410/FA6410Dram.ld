/*
 *  Linker script, fa s3c6410 board, 256M Mobile DDR RAM, 32bit
 */
 
 ENTRY(start) 

 MEMORY
   {
      dram0(wx) : ORIGIN = 0x50000000, LENGTH = 256M
   }
 SECTIONS
   {
    .start : 
    {
        *(.start)
    }
   } 
   
   
   