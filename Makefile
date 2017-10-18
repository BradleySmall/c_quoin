##
## Author: Bradley M. Small
## Copyright (c) 2014 All rights reserver
##
## Generic Makefile for development
##
.SECONDEXPANSION :
.SECONDARY :
.DELETE_ON_ERROR:

OUTDIR=build
SRCDIR=src
HDRS=$(wildcard $(SRCDIR)/*.h)
SRCS=$(wildcard $(SRCDIR)/*.c)
DEPS=$(HDRS) $(SRCS) Makefile
PROJ=$(notdir $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST))))))
RBINDIR := $(OUTDIR)/release/bin
DBINDIR := $(OUTDIR)/debug/bin
ROBJDIR := $(OUTDIR)/release/tmp/bin
DOBJDIR := $(OUTDIR)/debug/tmp/bin
ROBJS := $(SRCS:$(SRCDIR)/%.c=$(ROBJDIR)/%.o)
DOBJS := $(SRCS:$(SRCDIR)/%.c=$(DOBJDIR)/%.o)
CPPFLAGS = -I./$(SRCDIR)/
# CC=clang
# CFLAGS = -Weverything
##############
#Target Specific settings
##############
debug   : OBJDIR = $(DOBJDIR)
debug   : OBJS   = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
debug   : CFLAGS = -std='c11' -g3 -Wall -Wextra
debug   : BIN    = $(DBINDIR)/$(PROJ)
release : OBJDIR = $(ROBJDIR)
release : OBJS   = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
release : CFLAGS = -std='c11' -O2 -Wall -Wextra
release : BIN    = $(RBINDIR)/$(PROJ)

TIDY=/usr/bin/clang-tidy -checks='*, -llvm-header-guard' 

.PHONY : all debug release tidy

all : debug release

%/ :
	mkdir -p '$(@)'

debug : $$(BIN) 

release : $$(BIN) 

tidy : $(SRCS) $(HDRS)
	#| compile_commands.json
	$(TIDY)  $^ -- $(CPPFLAGS)

compile_commands.json : $(SRCS)
	bear make 

$(DOBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS) | $$(@D)/
	$(COMPILE.c) $(OUTPUT_OPTION) $< 

$(ROBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS) | $$(@D)/
	$(COMPILE.c) $(OUTPUT_OPTION) $< 

##$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPS) | $$(@D)/
##	$(COMPILE.c) $(OUTPUT_OPTION) $< 

#%.o: %.c $(DEPS) | $$(@D)/
#	$(COMPILE.c) $(OUTPUT_OPTION) $< 
#
#$(BIN) : $(OBJS) | $$(@D)/
#	$(LINK.c) $(OUTPUT_OPTION) $^

$(DBINDIR)/$(PROJ) : $(DOBJS) | $$(@D)/
	$(LINK.c) $(OUTPUT_OPTION) $^
	
$(RBINDIR)/$(PROJ) : $(ROBJS) | $$(@D)/
	$(LINK.c) $(OUTPUT_OPTION) $^

clean :
	$(RM) -r $(OUTDIR) compile_commands.json

