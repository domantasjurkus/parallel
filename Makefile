all: EncryptSHA512 CrackAZ99 example

EncryptSHA512: EncryptSHA512.c
	cc -o EncryptSHA512 EncryptSHA512.c -lcrypt

CrackAZ99: CrackAZ99.c
	cc -o CrackAZ99 CrackAZ99.c -lcrypt -lpthread

crack: CrackAZ99.c
	gcc -o crack CrackAZ99.c -lpthread

clean:
	rm -f a.out *~ EncryptSHA512 CrackLc3 CrackAZ99
	
example:
	gcc -o Threads Threads.c -lpthread

