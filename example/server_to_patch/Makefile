

# Flags passed to the preprocessor.
PPFLAGS += -I../.. 

# Flags passed to the C++ compiler.
#CCFLAGS += -g -MMD -Wall -Wno-sign-compare  
CCFLAGS += -g -rdynamic 

# Flags passed to the linker
LDFLAGS += -ldl -rdynamic 

HOTFIX_LIB = ../../libhotfix.a

EXE = server.x

SRCS = server.c func_c.c 

OBJS = $(SRCS:.c=.o)
#OBJS = $(subst .c,.o,$(SRCS))

all: $(EXE) 

$(HOTFIX_LIB):
	make all -C ../.. 

%.o: %.c 
	gcc $(PPFLAGS) $(CCFLAGS) -c $<

$(EXE): $(OBJS) $(HOTFIX_LIB)
	gcc $(CCFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(EXE) $(OBJS) 

