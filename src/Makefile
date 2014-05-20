# Copyright (C) 2014 Christian Hujer.
# All rights reserved.
# Licensed under GPLv3.
# See file LICENSE in the root directory of this project.

OBJS:=$(patsubst %.c,%.o,$(wildcard *.c))

CPPFLAGS:=-I../include -MMD --std=c99
.PHONY: all
all: keilwrapper.a($(OBJS))

.PHONY: clean
clean:
	$(RM) *.[aod]

include $(wildcard *.d)
