CFLAGS=-std=gnu99 -pthread
CC=gcc

%.o: %.c
	$(CC) $(CFLAGS) $< -c > $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c > $@

test: ./ProgressOutput_test.test
	./$<

ProgressOutput_test.test: ProgressOutput.o ProgressOutput_test.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf ./*.o ./*.test
