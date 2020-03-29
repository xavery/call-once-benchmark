LIBBENCHMARK_DIR := libbenchmark
LIBBENCHMARK_LIB := $(LIBBENCHMARK_DIR)/build/src/libbenchmark.a

benchmark : benchmark.cpp do_stuff.cpp selfmod.o $(LIBBENCHMARK_LIB)
	g++ -O2 -march=native -I$(LIBBENCHMARK_DIR)/include -o $@ $^ -pthread

%.o : %.asm
	nasm -f elf64 -l selfmod.lst -o $@ $^
