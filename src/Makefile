# Copyright (C) 2014 Christian Hujer.
# All rights reserved.
# Licensed under GPLv3.
# See file LICENSE in the root directory of this project.

OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))

## Specifies the installation prefix (used by install).
# Current value is: $(PREFIX)
PREFIX?=/usr/local/
help: export PREFIX:=$(PREFIX)

AR.old:=$(AR)
AR=flock $@.lock $(AR.old)
ARFLAGS:=rcs
CPPFLAGS:=-MMD
CPPFLAGS+=-I../include
CFLAGS:=-std=gnu99 -W -Wall -pedantic -Werror -fdiagnostics-show-option -Wno-unused-parameter -g

PROGRAMNAME:=kwcc

.PHONY: all
## Builds the program.
all: $(PROGRAMNAME)

.PHONY: clean
## Removes the generated files.
clean:
	$(RM) $(PROGRAMNAME) *.[aod]

.PHONY: tags
## Creates a tags file.
tags: $(wildcard *.[ch])
	ctags $^

.PHONY: indent
## Indents the source code.
indent:
	indent -npro -kr -nut -l1000 -c1 $(wildcard *.c)

.PHONY: install
## Installs the program, building it first if not built already.
# The program will be installed by copying it into the bin/ directory at the location specified by the PREFIX variable.
# I.e. if PREFIX is /usr/local/, the program will be installed in /usr/local/bin/.
# PREFIX is $(PREFIX), so the installation would be into $(PREFIX)/bin/
install: all
	cp $(PROGRAMNAME) $(PREFIX)/bin/

.PRECIOUS: %.o
$(PROGRAMNAME): kwcc.a
kwcc.a: kwcc.a($(filter-out $(PROGRAMNAME).o,$(OBJS)))

.PHONY: help
## Prints this help message.
help: makehelp.pl
	perl makehelp.pl $(MAKEFILE_LIST)

makehelp.pl:
	wget -N -q --no-check-certificate https://github.com/christianhujer/makehelp/raw/master/makehelp.pl

include $(wildcard *.d)
