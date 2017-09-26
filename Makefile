CFLAGS = -Wall -Wextra
CXXFLAGS = $(CFLAGS)

GCC=gcc $(CFLAGS) -ggdb -pthread
GCCSO=$(GCC) -fPIC -shared
CPP=g++ $(CXXFLAGS) -ggdb -pthread
CPPSO=$(CPP) -fPIC -shared

EXEC=cd cd.so

all: $(EXEC)

.PHONY: module
module: all

clean:
	/bin/rm -f $(EXEC)

cd: cd.c
	$(CPP) -o $@ $<
cd.so: cd.c
	$(CPPSO) -o $@ $<
