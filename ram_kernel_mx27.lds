ENTRY(Begin)

SECTIONS                   
{
  . = 0xA0004000;
  . = ALIGN(4);   
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
}
