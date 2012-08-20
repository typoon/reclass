CC=gcc
JAVAC=javac
FLAGS=-Wall -L../bin -I../ -lreclass -ggdb

all:
	pwd
	$(CC) ex1.c -o ex1 $(FLAGS)
	$(CC) ex2.c -o ex2 $(FLAGS) 
	$(CC) ex3.c -o ex3 $(FLAGS) 
	
	$(JAVAC) ex3.java

clean:
	@rm ex1 ex2 ex3 ex3.class
