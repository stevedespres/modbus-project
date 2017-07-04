################################################################################
# MAKEFILE    : ModbusTCPTest
# COMETIDO    : Test para prueba de programacion ModbusTCP
# VERSIONES   : V1.00 - Inicio = 12-01-2017 - Final = 12-01-2017 - Fede Pérez
# COMENTARIOS : V1.00 - Versión inicial
################################################################################

#===============================================================================
# User compiling options
#===============================================================================

#HOST: PC, PCLINUX, ARM
HOST := PC
#HOST := PCLINUX
#HOST :: ARM

#TARGET: PC, ARM, RASPBERRYPI
#TARGET := PC
#TARGET := ARM
TARGET := RASPBERRYPI

#DEBUG: YES, NO
DEBUG := NO

#===============================================================================
# Compiling options
#===============================================================================
#-------------------------------------------------------------------------------
# Determine compiling environment #ENVIRONMENT: CYGWIN,LINUX,WCROSS,LCROSS,ARM
#-------------------------------------------------------------------------------

ifeq ($(HOST),PC)
  ifeq ($(TARGET),PC)
    ENVIRONMENT := CYGWIN
  else
    ENVIRONMENT := WCROSS
  endif
else
  ifeq ($(HOST),LINUXPC)
    ifeq ($(TARGET),PC)
      ENVIRONMENT := LINUX
    else
      ENVIRONMENT := LCROSS
    endif
  else
    ifeq ($(HOST),ARM)
      ENVIRONMENT := ARM
    endif
  endif
endif

#-------------------------------------------------------------------------------
# Customize: WIN32 (CYGWIN)
#-------------------------------------------------------------------------------

ifeq ($(ENVIRONMENT),CYGWIN)
  PREFIX    := 
  BINPREFIX := 
  CFLAGS    := -std=gnu99 -Wno-write-strings
  CFLAGS    += -D_WIN32_ -D__CYGWIN__ -D_$(TARGET)_
  CPPFLAGS  := -pipe -g2 -Wall -Wno-write-strings -Wno-reorder
  CPPFLAGS  += -D_WIN32_ -D__CYGWIN__ -D_$(TARGET)_
  LDFLAGS   := -enable-auto-import
  LIBEXT    := .a
  BINEXT    := .exe
endif

#-------------------------------------------------------------------------------
# Customize: LINUX (LINUX)
#-------------------------------------------------------------------------------

ifeq ($(ENVIRONMENT),LINUX)
  PREFIX    := 
  BINPREFIX := 
  CFLAGS    := -std=gnu99 -Wno-write-strings
  CFLAGS    += -D_LINUX_ -D_$(TARGET)_
  CPPFLAGS  := -Wno-write-strings -Wno-reorder
  CPPFLAGS  += -D_LINUX_ -D_$(TARGET)_
  LDFLAGS   := -g
  LIBEXT    := .a
  BINEXT    := .out
endif

#-------------------------------------------------------------------------------
# Customize: Cross-compiling CYGWIN to ARM-LINUX-LINARO (WCROSS)
#-------------------------------------------------------------------------------

ifeq ($(ENVIRONMENT),WCROSS)
  PREFIX    := arm-linux-gnueabihf-
  BINPREFIX := /cygdrive/c/Linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09/bin/
  CFLAGS    := -std=gnu99 -Wno-write-strings
  CFLAGS    += -D_LINUX_ -D_$(TARGET)_
  CPPFLAGS  := -Wno-write-strings -Wno-reorder
  CPPFLAGS  += -D_LINUX_ -D_$(TARGET)_
  LDFLAGS   := -g
  LIBEXT    := .a
  BINEXT    := .out
endif

#-------------------------------------------------------------------------------
# Customize: Cross-compiling LINUX to ARM-LINUX-LINARO (LCROSS)
#-------------------------------------------------------------------------------

ifeq ($(ENVIRONMENT),LCROSS)
  PREFIX    := arm-linux-gnueabihf-
  BINPREFIX := /usr/local/Linaro/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09/bin/
  CFLAGS    := -std=gnu99 -Wno-write-strings
  CFLAGS    += -D_LINUX_ -D_$(TARGET)_
  CPPFLAGS  := -Wno-write-strings -Wno-reorder
  CPPFLAGS  += -D_LINUX_ -D_$(TARGET)_
  LDFLAGS   := -g
  LIBEXT    := .a
  BINEXT    := .out
endif

#-------------------------------------------------------------------------------
# Customize: ARM-LINUX-LINARO (ARM)
#-------------------------------------------------------------------------------

ifeq ($(ENVIRONMENT),ARM)
  PREFIX    := 
  BINPREFIX := 
  CFLAGS    := -std=gnu99 -Wno-write-strings
  CFLAGS    += -D_LINUX_ -D_$(TARGET)_
  CPPFLAGS  := -Wno-write-strings -Wno-reorder
  CPPFLAGS  += -D_LINUX_ -D_$(TARGET)_
  LDFLAGS   := -g
  LIBEXT    := .a
  BINEXT    := .out
endif

#-------------------------------------------------------------------------------
# Compiling and linking features - Paths and libraries
#-------------------------------------------------------------------------------

CINC_PATH := $(INCLUDE)

CLIB_PATH := $(CLIB_PATH)

ifeq ($(ENVIRONMENT),ARM)
  CINC_PATH += -I/usr/local/include
  CLIB_PATH += -L/usr/local/lib
endif

ifeq ($(DEBUG),YES)
  LIBSUBFIX := d
  CPPFLAGS  += -D_DEBUG_
else
  LIBSUBFIX :=
  CPPFLAGS  +=
endif

LDADDLIBS += -lpthread -lrt -lm -lstdc++

#===============================================================================
# Building tools
#===============================================================================

CC   := @$(BINPREFIX)$(PREFIX)gcc
CXX  := @$(BINPREFIX)$(PREFIX)g++
LD   := @$(BINPREFIX)$(PREFIX)ld
AR   := @$(BINPREFIX)$(PREFIX)ar
MD   := @mkdir -p
RM   := @rm -rf
ECHO := @echo

#===============================================================================
# File pathts
#===============================================================================

SRCDIR := .
OBJPATH := ./OBJ
LIBPATH := ./LIB
GENPATH := ./BIN

#===============================================================================
# Source files
#===============================================================================

MODBUSTCP_HOME := $(SRCDIR)/ModbusTCP
C_SRCS_LIBMODBUS := \
$(MODBUSTCP_HOME)/libModbus/src/modbus-data.c \
$(MODBUSTCP_HOME)/libModbus/src/modbus-rtu.c \
$(MODBUSTCP_HOME)/libModbus/src/modbus-tcp.c \
$(MODBUSTCP_HOME)/libModbus/src/modbus.c

MAIN_HOME := $(SRCDIR)/ModbusTCPTest
CPP_SRCS_MAIN := $(MAIN_HOME)/ModbusTCPTest.cpp 

#===============================================================================
# Object files
#===============================================================================

OBJS_MODBUSTCP := $(patsubst $(MODBUSTCP_HOME)/libModbus/src/%.c, \
                    $(OBJPATH)/%.c.o, \
                    $(C_SRCS_LIBMODBUS))

OBJS_MAIN := $(patsubst $(MAIN_HOME)/%.cpp, \
               $(OBJPATH)/%.cpp.o, \
               $(CPP_SRCS_MAIN))

#===============================================================================
# Building options
#===============================================================================

# Include paths
CINC_PATH += -I $(MAIN_HOME)/include -I $(MODBUSTCP_HOME)/libModbus/include

# Library paths
CLIB_PATH += -L$(LIBPATH) 

# Compiling and Linking options
CFLAGS   := $(CINC_PATH) $(CFLAGS) 
CPPFLAGS := $(CINC_PATH) $(CPPFLAGS)
LDFLAGS  := $(CLIB_PATH) $(LDFLAGS)

#===============================================================================
# Building targets
#===============================================================================

LIBMODBUSTCP := $(LIBPATH)/libModbusTCP$(LIBEXT)
BINMAIN := $(GENPATH)/ModbusTCPTest$(BINEXT)

#-------------------------------------------------------------------------------
# All targets
#-------------------------------------------------------------------------------
.PHONY: all
all: dirs $(LIBMODBUSTCP) $(BINMAIN)

#-------------------------------------------------------------------------------
# Building directories
#-------------------------------------------------------------------------------
dirs:
	$(MD) $(OBJPATH)
	$(MD) $(LIBPATH)
	$(MD) $(GENPATH)

#-------------------------------------------------------------------------------
# Targets
#-------------------------------------------------------------------------------
$(LIBMODBUSTCP): $(OBJS_MODBUSTCP)
	$(ECHO) 'Building library: $@'
	$(AR) rcs $@ $(OBJS_MODBUSTCP)

$(BINMAIN): $(OBJS_MAIN) $(LIBMODBUSTCP) 
	$(ECHO) 'Building target: $@'
	$(CC) $(OBJS_MAIN) -o$@ $(LDFLAGS) $(LIBMODBUSTCP) $(LDADDLIBS) 

#-------------------------------------------------------------------------------
# Compiling
#-------------------------------------------------------------------------------

# File compiling: ModbusTCP ----------------------------------------------------
$(OBJPATH)/modbus-data.c.o: $(MODBUSTCP_HOME)/libModbus/src/modbus-data.c
	$(ECHO) 'Building file: $<'
	$(CC) -c $(CFLAGS) -o$@ $<

$(OBJPATH)/modbus-rtu.c.o: $(MODBUSTCP_HOME)/libModbus/src/modbus-rtu.c
	$(ECHO) 'Building file: $<'
	$(CC) -c $(CFLAGS) -o$@ $<

$(OBJPATH)/modbus-tcp.c.o: $(MODBUSTCP_HOME)/libModbus/src/modbus-tcp.c
	$(ECHO) 'Building file: $<'
	$(CC) -c $(CFLAGS) -o$@ $<

$(OBJPATH)/modbus.c.o: $(MODBUSTCP_HOME)/libModbus/src/modbus.c
	$(ECHO) 'Building file: $<'
	$(CC) -c $(CFLAGS) -o$@ $<

# File compiling: Main Programs ------------------------------------------------
$(OBJPATH)/%.cpp.o: $(MAIN_HOME)/%.cpp 
	$(ECHO) 'Building file: $<'
	$(CXX) -c $(CPPFLAGS) -o$@ $<
	
	
#===============================================================================
# Clean
#===============================================================================
.PHONY: clean
clean:
	$(ECHO) 'Removing...'
	$(RM) ${OBJPATH}/*.o ${OBJPATH}/*.err ${OBJPATH}/*.map
	$(RM) ${GENPATH}/*.o ${GENPATH}/*.out ${GENPATH}/*.exe ${GENPATH}/*.tmp 
	$(RM) ${SRCDIR}/*.a ${OBJPATH}/*.a ${LIBPATH}/*.a ${GENPATH}/*.a
	$(RM) ${SRCDIR}/*.so ${OBJPATH}/*.so ${LIBPATH}/*.so ${GENPATH}/*.so
	$(RM) ${SRCDIR}/*.out.stackdump ${SRCDIR}/*.exe.stackdump 
	$(RM) ${GENPATH}/*.out.stackdump ${GENPATH}/*.exe.stackdump 
	$(RM) ${OBJPATH} ${LIBPATH} ${GENPATH}
	$(RM) ./*.o ./*.out ./*.exe ./*.a ./*.so ./*.err ./*.map
	$(RM) ./*.out.stackdump ./*.exe.stackdump
	$(ECHO) 'Files removed'
