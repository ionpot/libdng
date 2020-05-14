OUT := libdng.a

SHELL := sh
OS := $(shell uname)
MINGW := /c/MinGW

IDIR := include
SDIR := src
ODIR := obj

SPAT = $(SDIR)/%.c
OPAT = $(ODIR)/%.o

OFILE = $(ODIR)/$*.o

CC := gcc
CFLAGS := -march=native -Wall -Wextra -std=c99
COMPILE = $(CC) $(CFLAGS)

IDIRS := ./$(IDIR)
LDIRS :=

ifneq (,$(findstring MINGW,$(OS)))
	IDIRS += $(MINGW)/include
	LDIRS += $(MINGW)/lib
endif

CFLAGS += $(IDIRS:%=-I%)
CFLAGS += $(LDIRS:%=-L%)

CFILES := $(wildcard $(SDIR)/*.c)
OFILES := $(CFILES:$(SPAT)=$(OPAT))

.PHONY: all
all: $(OUT)

$(OUT): $(OFILES)
	$(AR) rcs $@ $^

$(OPAT): $(SPAT)
	$(COMPILE) -o $(OFILE) -c $<

$(OFILES): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

.PHONY: clean
clean:
	rm -rf $(ODIR) $(OUT)

.PHONY: check
check:
	$(CC) $(CFLAGS) -fsyntax-only $(CFILES)
