CC=gcc
FLAGS=-Wall -fPIC -ggdb
#FLAGS += -DDEBUG

PROG=libreclass
OBJS=$(shell ls *.c | grep -v reclass_dumper.c | sed -e "s/\.c/.o/g")
HEADERS=$(shell ls *.h)
YACC=bison

PREFIX=/usr/local
INSTALL_INCLUDE_DIR=/usr/include/reclass
INSTALL_LIBS_DIR=$(PREFIX)/lib
INSTALL_BIN_DIR=$(PREFIX)/bin

all: shared static tools

parser:
	bison -d parser.y
	flex parser.l
	$(CC) $(FLAGS) parser.tab.c parser.tab.h -c
	$(CC) $(FLAGS) lex.yy.c -c
	
	$(eval $OBJS+=parser.tab.o lex.yy.o)
	
shared: parser $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lfl -shared -o bin/$(PROG).so

static: parser $(OBJS)
	ar rcs bin/$(PROG).a $(OBJS)

tools:
	$(CC) $(FLAGS) reclass_dumper.c -lreclass -L./bin -I. -o bin/reclass_dumper

%.o: %.c
	$(CC) $(FLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f *.so
	@rm -f *.a
	@rm -f *.gch
	@rm -f parser.tab.c parser.tab.h lex.yy.c
	@rm -rf bin/*.so
	@rm -rf bin/*.a
	@rm -rf bin/reclass_dumper

install:
	#@mkdir $(INSTALL_INCLUDE_DIR)
	cp $(HEADERS) $(INSTALL_INCLUDE_DIR)
	cp bin/*.so   $(INSTALL_LIBS_DIR)
	cp bin/*.a    $(INSTALL_LIBS_DIR)
	cp bin/reclass_dumper $(INSTALL_BIN_DIR)
	ldconfig
