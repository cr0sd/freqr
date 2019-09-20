all:
	cc freqr.c -o freqr -Wall -Wextra -lm
clean:
	@rm -f *.o freqr
