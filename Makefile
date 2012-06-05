CC=gcc
FLAGS=-Wall -fPIC -ggdb -DDEBUG -lfl
#FLAGS += -DDEBUG

PROG=libreclass
OBJS=$(shell ls *.c | sed -e "s/\.c/.o/g")
HEADERS=$(shell ls *.h)

PREFIX=/usr/local
INSTALL_INCLUDE_DIR=/usr/include/reclass
INSTALL_LIBS_DIR=$(PREFIX)/lib

all: shared static

parser:
	bison -d parser.y
	flex parser.l
	$(CC) $(FLAGS) parser.tab.c parser.tab.h -c
	$(CC) $(FLAGS) lex.yy.c -c
	
	$(eval $OBJS+=parser.tab.o lex.yy.o)
	
shared: parser $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -shared -o bin/$(PROG).so

static: parser $(OBJS)
	ar rcs bin/$(PROG).a $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f *.so
	@rm -f *.a
	@rm -f parser.tab.c parser.tab.h lex.yy.c

install:
	@mkdir $(INSTALL_INCLUDE_DIR)
	cp $(HEADERS) $(INSTALL_INCLUDE_DIR)
	cp bin/* $(INSTALL_LIBS_DIR)
	ldconfig
