CC = clang++
CFLAGS = -I/opt/local/include
LDFLAGS = -L/opt/local/lib -lgflags -lglog -lzmq -g0 -O3

all: broker sink source worker

clean:
	rm -f *.o broker sink source worker

broker: broker.o
	$(CC) $(LDFLAGS) $^ -o $@

sink: sink.o
	$(CC) $(LDFLAGS) $^ -o $@

source: source.o
	$(CC) $(LDFLAGS) $^ -o $@

worker: worker.o
	$(CC) $(LDFLAGS) $^ -o $@

# compile
%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

