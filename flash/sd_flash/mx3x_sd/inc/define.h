

// MX31_MsilFabTest:

#define iRamCcmBufAdd 0x1FFFC000
#define CcmMaxWordSize 128 // 1KByte
#define iRamCodeBufAdd 0x1FFFC400
#define CodeMaxWordSize 2304 // 9KByte  



// Address ranges for Production parts: 

#define NFCstart	0xB8000000 // Tortola
#define NFCend		0xB8000FFF // Tortola

#define WEIMstart	0xB8002000 // Tortola
#define WEIMend		0xB8002060 // Tortola

#define MemoryStart 0x80000000 // Tortola
#define MemoryEnd	0xB7FFFFFF // Tortola
#define Memory_MaxLength	(MemoryEnd - MemoryStart + 1)

#define CCMstart	0x53f80000 // Tortola
#define CCMend		0x53f80064 // Tortola 

#define ESDCTLstart	0xB8001000 // Tortola
#define ESDCTLend	0xB8001FFF // Tortola



