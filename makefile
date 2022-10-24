# makes a.out for string_tester file

all: a.out

FLAGS = -Wall -Wno-char-subscripts
a.out: string_tester.c aes_cbc.c aes_cbc.h augustus.c augustus.h caesar.c caesar.h default_tests.c default_tests.h strings.c strings.h
	@echo 'building a.out'
	gcc -o a.out string_tester.c aes_cbc.c augustus.c caesar.c default_tests.c strings.c $(FLAGS)

clean:
	rm -f a.out *.o

