include rules.make

CHECK=y
export UNIT_TEST=n

OBJS = init/init.o ram_kernel/ramkernel.o fuse/fuselib.o flash/flashlib.o
UT_OBJS = $(OBJS)

FTYPE = $(shell echo $(FLASH_TYPE) | tr '[A-Z]' '[a-z]')
FMODEL = $(shell echo $(FLASH_MODEL) | tr '[A-Z]' '[a-z]')
ifeq ($(FTYPE),nor)
TARGET = bin/$(MCU)$(REV)_$(FTYPE)_$(FMODEL).elf
else
TARGET = bin/$(MCU)$(REV)_$(FTYPE).elf
endif
BINFILE = $(patsubst %.elf, %.bin, $(TARGET))
MAPFILE = $(strip $(patsubst %.elf, %.map, $(TARGET)))
LDSFILE = ram_kernel_$(MCU).lds

UT_TARGET = bin/$(MCU)$(REV)_unittest.elf
UT_BINFILE = $(patsubst %.elf, %.bin, $(UT_TARGET))
UT_MAPFILE = $(strip $(patsubst %.elf, %.map, $(UT_TARGET)))

ifeq ($(strip $(MCU)),)
CHECK=n
endif
ifeq ($(strip $(FLASH_TYPE)),)
CHECK=n
endif

all: check 
	@echo
	@echo [Building initial ...]
	make -C init/
	@echo
	@echo [Building RAM Kernel ...]
	make -C ram_kernel/ all
	@echo
	@echo [Building Flash Library ...]
	make -C flash/ all
	@echo
	@echo [Building Fuse Library ...]
	make -C fuse/ all
	@echo
	@echo [Generate RAM Kernel image ...]
	$(CC) -nostartfiles -static -Wl,-Map,$(MAPFILE) -T$(LDSFILE) -o $(TARGET) $(OBJS)
	$(OBJCOPY) -O binary -j .fhdr -j .text  -j .data -j .bss $(TARGET) $(BINFILE)


y:
	@echo start building ...
n:
	@echo please use the following build command:
	@echo =========================================================================
	@echo make MCU={user input} REV={user input} [unittest/flashlib] FLASH_TYPE={user input} FLASH_MODEL={user input}     
	@echo 
	@echo support i.MX  type: mx25 mx27 mx31 mx32 mx35 mx37 mx51 mx53
	@echo REV, User specify chip reversion, to1, to2, ...
	@echo support flash type: nor nand mmc sd spi
	@echo support nor flash model:
	@echo 		nor: spansion
	@echo -------------------------------------------------------------------------          
	@echo make clean
	@echo Clean all the out file		
	@echo make install DEST={user input directory}
	@echo copy the bin file to user input directory
	@echo =========================================================================
	exit 1; 

check: $(CHECK)

flashlib: check 
	@echo
	@echo [Building initial ...]
	make -C init/
	@echo
	@echo [Building RAM Kernel ...]
	make -C ram_kernel/ all
	@echo
	@echo [Building Flash Library ...]
	make -C flash/ all
	make -C fuse/ all UNIT_TEST=y
	@echo [Generate RAM Kernel image ...]
	$(CC) -nostartfiles -static -Wl,-Map,$(MAPFILE) -T$(LDSFILE) -o $(TARGET) $(OBJS)
	$(OBJCOPY) -O binary -j .fhdr -j .text  -j .data -j .bss $(TARGET) $(BINFILE)

unittest: $(UT_TARGET) $(UT_BINFILE)

$(UT_TARGET):
	make -C init/
	make -C ram_kernel/
	make -C fuse/ UNIT_TEST=y
	make -C flash/ UNIT_TEST=y
	$(CC) -nostartfiles -static -Wl,-Map,$(UT_MAPFILE) -T$(LDSFILE) -o $@ $(UT_OBJS)

$(UT_BINFILE):$(UT_TARGET)
	$(OBJCOPY) -O binary -j .text  -j .data -j .bss $< $@



install:
	@echo copy files to the directory:$(DEST)
	$(CP) -f bin/*.bin $(DEST)

clean:
	make -C ram_kernel/ clean
	make -C fuse/ clean
	make -C flash/ clean
	make -C init/ clean
	rm -f bin/*.elf
	rm -f bin/*.map
