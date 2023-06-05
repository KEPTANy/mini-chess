SRCS = src/color.c \
	   src/piece.c \
	   src/square.c

test: test/test.c clean
	$(CC) -o build/test test/test.c $(SRCS)

build: src/main.c clean
	$(CC) -o build/mini-chess src/main.c $(SRCS)

clean:
	rm -rf build/*
