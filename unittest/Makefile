ACEUNIT_HOME:= ../../aceunit/src/native/
vpath %.c $(ACEUNIT_HOME) $(ACEUNIT_HOME)/loggers/

CPPFLAGS+=-I $(ACEUNIT_HOME) -MMD -DACEUNIT_SUITES -std=c99
CFLAGS:=-W -Wall -pedantic -Werror -fdiagnostics-show-option -g

LDFLAGS:=-Wl,-Map=AceUnitMain.map

ACEUNIT_OBJECTS:= \
    AceUnitData.o \
    AceUnitMain.o \
    AceUnit.o \
    FullPlainLogger.o \
    Suite1.o \

TEST_OBJECTS:= \
    ArchTest.o \
    ArgConvTest.o \
    ArrayTest.o \
    ExpectWrapTest.o \
    FileSuffixTest.o \
    PathTest.o \
    ToolTest.o \

PRODUCTION_OBJECTS:= \
    Arch.o \
    ArgConv.o \
    FileSuffix.o \
    Path.o \
    StringArray.o \
    Tool.o \

vpath %.c ../src

.PHONY: all
## Builds and runs the unit tests.
# Same as test.
all: test

-include $(wildcard *.d)

## Builds an runs the unit tests.
test: AceUnitMain
	./AceUnitMain
	touch test

AceUnitMain: $(ACEUNIT_OBJECTS) $(TEST_OBJECTS) $(PRODUCTION_OBJECTS)

$(TEST_OBJECTS) Suite1.c: runAceUnit

runAceUnit: $(TEST_OBJECTS:.o=.c)
	java -ea -jar $(ACEUNIT_HOME)../java/AceUnit.jar --exit true .
	touch $@

.PHONY: clean
## Removes all auto-generated files.
clean:
	$(RM) *.o AceUnitMain *.d Suite*.c *Test.h test runAceUnit *.map

.PHONY: distclean
## Removes all auto-generated and downloaded files.
distclean: clean
	$(RM) makehelp.pl

makehelp.pl:
	wget -N -q --no-check-certificate https://github.com/christianhujer/makehelp/raw/master/makehelp.pl

.PHONY: help
## Prints this help text.
help: makehelp.pl
	@perl makehelp.pl $(MAKEFILE_LIST)
