
CC := g++
LIBC := ar rsv
INCLUDE := -I include
CPPFLAGS := -c -Wall

srcdir := src
objdir := build
bindir := bin
incdir := include
testdir := tests
libdir := lib

EXE := $(bindir)//aescrypto.exe
LIB := $(libdir)//libaescrypto.a
SRCS := $(wildcard $(srcdir)//*.cpp)
OBJS := $(patsubst $(srcdir)//%.cpp, $(objdir)//%.o, $(SRCS))

exe: $(EXE)

$(EXE): $(OBJS)
	$(CC) -g -o $@ $^ -lcryptopp -lpthread

lib: $(LIB)

$(LIB): $(OBJS)
	$(LIBC) $@ $^
	@echo Compilation success

$(objdir)//%.o: $(srcdir)//%.cpp
	$(CC) -g $(INCLUDE) $(CPPFLAGS) -o $@ $<


# Build Tests

tobjdir := $(testdir)//build
TESTSRCS := $(wildcard $(testdir)//*.cpp)
TESTOBJS := $(patsubst $(testdir)//%.cpp, $(tobjdir)//%.o, $(TESTSRCS))
TESTEXE := $(testdir)//runner

tests: $(TESTOBJS)
	$(CC) $^ -laescrypto -lcryptopp -o $(TESTEXE)

$(tobjdir)//%.o: $(testdir)//%.cpp
	$(CC) -I ..//$(incdir) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo Cleaning object files...
	rm -rf $(objdir)//*.o

tclean:
	@echo Cleaning test object files...
	rm -rf $(tobjdir)//*.o

updateLibrary:
	@echo Moving libaescrypto.a to c++ search path...
	cp -f lib/libaescrypto.a /usr/lib/
	@echo \nDone.

updateHeaders:
	@echo Moving header files to c++ search path...
	cp -f include/*.h /usr/include/
	@echo \nDone.
