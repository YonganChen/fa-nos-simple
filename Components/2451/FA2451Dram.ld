/*
 *  Linker script, fa s3c2451 board, DRAM0 128MB
 */
 
 ENTRY(start) 

 MEMORY
   {
      dram0(wx) : ORIGIN = 0x30000000, LENGTH = 128M
   }
 SECTIONS
   {
    .start : 
    {
        *(.start)
    }
   } 
   
   
   