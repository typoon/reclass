CC=gcc
FLAGS=-Wall -ggdb -Wno-format-contains-nul
LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH)

all:
	@cp ../*.h .
	@cp ../*.a .
	$(CC) $(FLAGS) usage_example1.c libreclass.a -o ue1
	$(CC) $(FLAGS) usage_example2.c libreclass.a -o ue2
	$(CC) $(FLAGS) hack.c libreclass.a -o hack
	$(CC) $(FLAGS) main.c libreclass.a -o main

clean:
	rm *.h
	rm *.a
	@rm ue1
	@rm ue2
	@rm main
