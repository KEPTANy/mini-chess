SRCS = src/attacks.c \
	   src/bitboard.c \
	   src/bitops.c \
	   src/color.c \
	   src/direction.c \
	   src/move.c \
	   src/piece.c \
	   src/position.c \
	   src/square.c

test: test/test.c clean
	$(CC) -o build/test test/test.c $(SRCS)

build: src/main.c clean
	$(CC) -o build/mini-chess src/main.c $(SRCS)

clean:
	rm -rf build/*
