include ../rules.make

GLOBAL_INC := ../global_inc

TARGET_PATH := src/platform/$(MCU)
SRC := $(wildcard $(TARGET_PATH)/src/*.c)

SRC_OBJS := $(patsubst %.c, %.o, $(SRC))
SRC_OBJS += src/main.o
OBJS := $(SRC_OBJS)

EXT_OBJS = $(wildcard obj/${MCU}/*.o)
OBJS += $(EXT_OBJS)

REV_MACRO = REV_$(shell echo $(REV) | tr '[a-z]' '[A-Z]')
CFLAGS += -D$(REV_MACRO)

INC = $(TARGET_PATH)/inc/
TARGET = ramkernel.o

all: $(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)

-include .depend

.PHONY: clean
clean:
	@find ./ -name "*.o" ! -ipath "\./obj/*" -exec rm -rf {} \;
	@rm -f .depend
