include ../rules.make

GLOBAL_INC = ../global_inc

TARGET = flashlib.o

ifeq ($(UNIT_TEST),y)
SRC = unit_test/fake_flashlib.c
INC = ./
else
ifeq ($(MCU), mx25)
MCU_ALIAS = $(MCU)
else
ifeq ($(MCU), mx51)
MCU_ALIAS = $(MCU)
else
ifeq ($(MCU), mx37)
MCU_ALIAS = $(MCU)
else
ifeq ($(MCU), mx35) 
MCU_ALIAS = $(MCU)
else
ifeq ($(findstring mx3, $(MCU)), mx3)
MCU_ALIAS = mx3x
else
MCU_ALIAS = $(MCU)
endif
endif
endif
endif
endif

MCU_MACRO = MCU_$(shell echo $(MCU) | tr '[a-z]' '[A-Z]')
REV_MACRO = REV_$(shell echo $(REV) | tr '[a-z]' '[A-Z]')

FTYPE = $(shell echo $(FLASH_TYPE) | tr '[A-Z]' '[a-z]')
FMODEL = $(shell echo $(FLASH_MODEL) | tr '[A-Z]' '[a-z]')
FLASH_PATH = $(FTYPE)_flash

ifeq ($(FTYPE), mmc)
TARGET_PATH = $(FLASH_PATH)/$(MCU_ALIAS)_mmc
endif
ifeq ($(FTYPE), nor)
TARGET_PATH = $(FLASH_PATH)/$(FMODEL)
CFLAGS += -D$(MCU_MACRO)
endif
ifeq ($(FTYPE), nand)
TARGET_PATH = $(FLASH_PATH)
CFLAGS += -D$(MCU_MACRO)
endif

ifeq ($(FTYPE), sd)
TARGET_PATH = $(FLASH_PATH)/$(MCU_ALIAS)_sd
endif

ifeq ($(FTYPE), spi)
TARGET_PATH = $(FLASH_PATH)
CFLAGS += -D$(MCU_MACRO)
endif

CFLAGS += -D$(REV_MACRO)

SRC = $(wildcard $(TARGET_PATH)/src/*.c)
INC = $(TARGET_PATH)/inc/ 

endif

OBJS = $(patsubst %.c, %.o, $(SRC))

-include .depend

all: $(OBJS)
	@echo "Start"
	@echo $(FLASH_PATH)
	@echo $(TARGET_PATH)
	@echo "End"
	$(LD) -r -o $(TARGET) $(OBJS)


.PHONY: clean
clean:
	@find ./ -name "*.o" -exec rm -rf {} \;
	@rm -f .depend
