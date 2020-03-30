CC=gcc
CFLAGS=-Wall
LIBFLAG= -lgmp
EXEC=mon_chall
BUILDDIR= build
all:mon_chall

mon_chall: createEnv verification.o findy.o
	$(CC) -g -o $(EXEC)  build/verification.o build/findy.o $(CFLAGS) $(LIBFLAG)

createEnv:
	mkdir -p $(BUILDDIR)


verification.o: verification.c
	$(CC) -g -o $(BUILDDIR)/$@ -c $< $(CFLAGS) $(LIBFLAG)

findy.o: findy.c verification.h
	$(CC) -g -o $(BUILDDIR)/$@ -c $< $(CFLAGS) $(LIBFLAG)
clean: 
	rm -rf $(BUILDDIR) $(EXEC)
