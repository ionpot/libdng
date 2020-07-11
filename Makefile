OUT := libdng.a

SHELL := sh
OS := $(shell uname)
MINGW := /c/MinGW

IDIR := include
SDIR := src
ODIR := obj
DDIR := dep

SPAT = $(SDIR)/%.c
DPAT = $(DDIR)/%.d
OPAT = $(ODIR)/%.o

DFILE = $(DDIR)/$*.d
OFILE = $(ODIR)/$*.o

CC := gcc
CFLAGS := -march=native -Wall -Wextra -std=c99
DFLAGS = -MT "$(OFILE) $(DFILE)" -MMD -MP -MF $(DFILE)
COMPILE = $(CC) $(CFLAGS) $(DFLAGS)

IDIRS := ./$(IDIR)
LDIRS :=

ifneq (,$(findstring MINGW,$(OS)))
	IDIRS += $(MINGW)/include
	LDIRS += $(MINGW)/lib
endif

CFLAGS += $(IDIRS:%=-I%)
CFLAGS += $(LDIRS:%=-L%)

CFILES := $(wildcard $(SDIR)/*.c)
DFILES := $(CFILES:$(SPAT)=$(DPAT))
OFILES := $(CFILES:$(SPAT)=$(OPAT))

.PHONY: all
all: $(OUT)

-include $(DFILES)

$(OUT): $(OFILES)
	$(AR) rcs $@ $^

$(OPAT) $(DPAT): $(SPAT)
	$(COMPILE) -o $(OFILE) -c $<

$(DFILES): | $(DDIR)
$(OFILES): | $(ODIR)

$(DDIR):
	mkdir $(DDIR)

$(ODIR):
	mkdir $(ODIR)

.PHONY: clean
clean:
	rm -rf $(DDIR) $(ODIR) $(OUT)

.PHONY: check
check: CFLAGS += -fsyntax-only
check: HFILES := $(wildcard $(IDIR)/*.h)
check:
	$(CC) $(CFLAGS) $(HFILES) $(CFILES)
