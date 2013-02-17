ENTRY(Begin)

SECTIONS                   
{
  . = 0x90004000;
  .fhdr : {
	  __flash_hdr_start__ = .;
	  LONG(0x90004020)
	  LONG(0x0)
	  LONG(0x0)
	  LONG(0x90004008)
	  LONG(0x0)
	  LONG(0x0)
	  LONG(0x0)
	  __flash_hdr_end__ = .;
  }
  . = ALIGN(0x10);   
  .text : {         
          _text = .; 
              init/init.o(.init)
              *(.text) 
          . = ALIGN(4);
          _etext = .;           
        } 
  . = ALIGN(4);     
  .data : { 
          _data = .;          
              *(.data)
              *(.rodata)
          . = ALIGN(4);
          _edata = .;  
         }    
  . = ALIGN(4);                        
  .bss : {                   
          __bss_start__ = .; 
            *(.bss) 
          . = ALIGN(4); 
          __bss_end__ = .; 
          }
          
	        end = . ; 
  . = 0x1FFE0000;
  .usb_buf : {
  	*(usb_buffer_no_init)
  	}
}
