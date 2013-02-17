
SOURCES:=$(wildcard *.c)

OBJS = $(SOURCES:.c=.o)

TEST_INJECT = test_inject.x 

CFLAGS = -O0 -g -I..  
LDFLAGS = -O0 -g  

all: $(TEST_INJECT)

inject.o: ../inject.c
	gcc $(CFLAGS) -c $<

%.o : %.c Makefile
	gcc $(CFLAGS) -c $<

$(TEST_INJECT): inject.o test_inject.o 
	gcc $(LDFLAGS) -o $@ $^

clean: 
	@rm -rf $(TEST_INJECT) *.o

