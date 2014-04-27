ACEUNIT_HOME:= ../../aceunit/src/native/
vpath %.c $(ACEUNIT_HOME) $(ACEUNIT_HOME)/loggers/

CPPFLAGS+=-I $(ACEUNIT_HOME) -MMD -DACEUNIT_SUITES -std=c99

.PHONY: all
## Builds and runs the unit tests.
# Same as test.
all: test

-include $(wildcard *.d)

## Builds an runs the unit tests.
test: AceUnitMain
	./AceUnitMain
	touch test

AceUnitMain: AceUnitMain.o AceUnit.o AceUnitData.o FullPlainLogger.o Suite1.o ExpectWrapTest.o

ExpectWrapTest.o: ExpectWrapTest.h

ExpectWrapTest.h Suite1.c: runAceUnit

runAceUnit: ExpectWrapTest.c
	java -ea -jar $(ACEUNIT_HOME)../java/AceUnit.jar --exit true .
	touch $@

.PHONY: clean
## Removes all auto-generated files.
clean:
	$(RM) *.o AceUnitMain *.d Suite*.c ExpectWrapTest.h test runAceUnit

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
