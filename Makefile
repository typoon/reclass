CC=gcc
FLAGS=-Wall -ggdb -DDEBUG
#FLAGS += -DDEBUG

PROG=libreclass
OBJS=$(shell ls *.c | sed -e "s/\.c/.o/g")

all: shared static

shared: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -shared -o $(PROG).so

static: $(OBJS)
	ar rcs $(PROG).a $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f *.so
	@rm -f *.a
