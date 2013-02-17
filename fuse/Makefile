include ../rules.make

GLOBAL_INC = ../global_inc

ifeq ($(UNIT_TEST),y)
OBJS = unit_test/fake_fuselib.o
INC = ./
else
OBJS = fuse_lib.o
INC = ./
endif
TARGET = fuselib.o
SRC = $(patsubst %.o, %.c, $(OBJS))

ifneq ("$(TO)", "")
CFLAGS += -DTO$(TO)
else
CFLAGS += -DTO1
endif

MCU_MACRO = $(shell echo $(MCU) | tr '[a-z]' '[A-Z]')
CFLAGS += -DMCU_$(MCU_MACRO)

REV_MACRO = REV_$(shell echo $(REV) | tr '[a-z]' '[A-Z]')
CFLAGS += -D$(REV_MACRO)

all: $(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)

-include .depend

.PHONY: clean
clean:
	@find ./ -name "*.o" -exec rm -rf {} \;
	@rm -f .depend
