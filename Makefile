CFLAGS=-std=gnu99 -pthread
CC=gcc

ProgressOutput_test.o: ProgressOutput_test.c
	$(CC) $(CFLAGS) $< -c > $@

ProgressOutput.o: ProgressOutput.c
	$(CC) $(CFLAGS) $< -c > $@

test: ./ProgressOutput_test.test
	./$<

ProgressOutput_test.test: ProgressOutput.o ProgressOutput_test.o
	$(CC) $(CFLAGS) $^ -o $@

