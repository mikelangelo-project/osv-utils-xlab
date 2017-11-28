CFLAGS = -Wall -Wextra
CXXFLAGS = $(CFLAGS)

GCC=gcc $(CFLAGS) -ggdb -pthread
GCCSO=$(GCC) -fPIC -shared
CPP=g++ $(CXXFLAGS) -ggdb -pthread
CPPSO=$(CPP) -fPIC -shared

EXEC=cd cd.so
EXEC+=sleep sleep.so
EXEC+=cat cat.so
EXEC+=echo echo.so
EXEC+=template template.so

all: $(EXEC)

.PHONY: module
module: all

clean:
	/bin/rm -f $(EXEC)

%: %.c
	$(CPP) -o $@ $<
%.so: %.c
	$(CPPSO) -o $@ $<
