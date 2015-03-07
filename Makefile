CC=g++
CFLAG=-g
OBJGROUP=test.o tmManager.o tmRandom.o tmTool.o lineController.o

all: test

test: $(OBJGROUP)
	$(CC) -o test $(OBJGROUP)

clean:
	\rm *.o
