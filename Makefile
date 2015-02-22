CC=g++
CFLAG=-g
OBJGROUP=test.o tmManager.o tmRandom.o tmTool.o

all: test

test: $(OBJGROUP)
	$(CC) -o test $(OBJGROUP)

clean:
	\rm *.o
