CFLAGS=-Wfatal-errors -Wall
LDFLAGS=-lm

ifeq ($(OS),Windows_NT)
#Windows/Cygwin
CFLAGS += -DCOMPILE_FOR_WINDOWS
endif

all:freqr
tests:freqr
	tests/tests.sh
clean:
	$(RM) *.o freqr
	tests/tests.sh clean
.PHONY: tests clean
