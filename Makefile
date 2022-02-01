OBJECTS = $(patsubst %.cpp,%.o, $(shell find lib/libfasthttpserver/ -name *.cpp))
CC = g++
CFLAGS = -I./lib/ -I./lib/libfasthttpserver -fPIC -c
LDFLAGS =

LIB_NAME = libfasthttpserver

OUT_FILE = $(LIB_NAME).so

.PHONY: install
install: build
	cp $(OUT_FILE) /usr/local/lib/

	rsync -arvz --progress --include='*.h' --include="*/" --exclude="*" ./lib/$(LIB_NAME)/ headers/
	cd /usr/local/include && mkdir $(LIB_NAME)

	cp -r headers/* /usr/local/include/$(LIB_NAME)/
	rm -r headers/

.PHONY: uninstall
uninstall:
	rm /usr/local/lib/$(LIB_NAME).so
	rm -r /usr/local/include/$(LIB_NAME)/

.PHONY: build
build: $(OBJECTS)
	$(CC) -shared -o $(OUT_FILE) $(OBJECTS)

.PHONY: all
all: $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)