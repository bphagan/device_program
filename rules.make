#/*****************************************************************************
#** rules.make
#**
#** Copyright 2007 Freescale Semiconductor, Inc. All Rights Reserved.
#**
#** This file contains copyrighted material. Use of this file is
#** restricted by the provisions of a Freescale Software License
#** Agreement, which has either been electronically accepted by
#** you or has been expressly executed between the parties.
#**
#** Description: Explanation for the usage of this file.
#**
#** Revision History:
#** -----------------
#*****************************************************************************/
CC = arm-elf-gcc
AS = arm-elf-as
LD = arm-elf-ld 
NM = arm-elf-nm
OBJDUMP = arm-elf-objdump
OBJCOPY = arm-elf-objcopy
READELF = arm-elf-readelf
RM = rm -f
RN = mv
CP = cp 
TOPDIR = $(shell pwd)
BIN  = arm-elf-objcopy
LIBDIR = "/cygdrive/c/Program Files/gnuarm/lib/gcc/arm-elf/4.1.1/"
SHELL = /bin/sh

CFLAGS = -Wall -Wstrict-prototypes -Wno-trigraphs  -nostartfiles -O0  -nostdlib \
					-static -feliminate-unused-debug-symbols -fno-strict-aliasing -fno-common \
				 	 -pipe -fno-builtin  -g -mapcs -mlittle-endian \
					-msoft-float -mfpu=fpa
ASFLAGS = -mapcs -mlittle-endian 

ifeq ($(findstring mx3, $(MCU)), mx3)
	CFLAGS += -mcpu=arm1136jf-s
	ASFLAGS+= -mcpu=arm1136jf-s
else
	ifeq ($(findstring mx2, $(MCU)), mx2)
		CFLAGS += -mcpu=arm926ej-s
		ASFLAGS+= -mcpu=arm926ej-s
	endif
endif
					
%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $<
	
%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INC) -I$(GLOBAL_INC) -o $@ $<
	$(CC) -MM -MT '$@' $(CFLAGS) -I$(INC) -I$(GLOBAL_INC) $< >> .depend
