CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -g -pedantic -std=c99
EXE = minimax

.PHONY: build
build: $(EXE) 

$(EXE): main.o trie.o MinMax.o queue.o deque.o bonus.o	
	$(CC) -o $@ $^

main.o: main.c 
	$(CC) $(CFLAGS) -o $@ -c $<

trie.o: trie.c
	$(CC) $(CFLAGS) -o $@ -c $<

MinMax.o: MinMax.c
	$(CC) $(CFLAGS) -o $@ -c $<

queue.o: queue.c
	$(CC) $(CFLAGS) -o $@ -c $<

deque.o: deque.c
	$(CC) $(CFLAGS) -o $@ -c $<

bonus.o: bonus.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: run
run: build
	./$(EXE)
	

.PHONY: clean
clean: build
	rm $(EXE) *.o

.PHONY: memcheck
memcheck: build
	valgrind \
        --tool=memcheck \
        --leak-check=full --leak-check-heuristics=all \
        --show-leak-kinds=all \
        --track-origins=yes \
        --error-exitcode=1 ./$(EXE)
