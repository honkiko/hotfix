
SOURCES:=$(wildcard *.c)

OBJS = $(SOURCES:.c=.o)

LIB_HOTFIX = libhotfix.a

CFLAGS = -O0 -g  
LDFLAGS = -O0 -g  

all: $(LIB_HOTFIX) 

%.o : %.c Makefile
	gcc $(CFLAGS) -c $<

$(LIB_HOTFIX): inject.o hotfix.o
	ar rc $(LIB_HOTFIX) $^
	ranlib $(LIB_HOTFIX)

clean: 
	@rm -rf $(LIB_HOTFIX) $(OBJS)

