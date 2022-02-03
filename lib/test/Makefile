CC = g++

.PHONY: build
build:
	$(CC) -o out.elf main.cpp -lfasthttpserver -ltcpserver -pthread

.PHONY: run
run:
	LD_LIBRARY_PATH=/usr/local/lib ./out.elf