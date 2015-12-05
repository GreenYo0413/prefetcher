CFLAGS = -msse2 --std gnu99 -O0 -Wall
SRCS = main.c

EXEC = naive_transpose sse_transpose sse_prefetch_transpose

all: $(EXEC)

naive_transpose: $(SRCS) naive_transpose.c naive_transpose.h
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS) $@.c

sse_transpose: sse_transpose.c sse_transpose.h
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS) $@.c

sse_prefetch_transpose: sse_prefetch_transpose.c sse_prefetch_transpose.h
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS) $@.c

run: $(EXEC)
	watch -d -t ./naive_transpose

clean:
	$(RM) $(EXEC) *.o perf.*
