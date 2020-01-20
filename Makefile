CFLAGS=-Wfatal-errors -Wall
LDFLAGS=-lm

ifeq ($(OS),Windows_NT)
#Windows/Cygwin
CFLAGS += -DCOMPILE_FOR_WINDOWS
endif

all:freqr
clean:
	$(RM) *.o freqr
