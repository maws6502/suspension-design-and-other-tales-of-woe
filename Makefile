CC=clang
CFLAGS=-I. -Wall -Wno-parentheses --std=c89# fight me
LDFLAGS=-lm
DEPS = suspsolv.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: test toe_change

test: test.o utils.o actuate_suspension.o worst_case_toe.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

toe_change: toe_change.o utils.o worst_case_toe.o actuate_suspension.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o toe_change test