CC=g++

DEBUG ?= 1

ifeq ($(DEBUG),1)
   OPTFLAGS=-g
else
   OPTFLAGS=-O3
endif

CFLAGS=-I. -I../src -I../CppUnitLite -std=c++20 -Wall -Werror $(OPTFLAGS) $(shell pkg-config --cflags opencv4)

PROJDIR := $(realpath $(CURDIR)/..)
BUILDDIR := $(PROJDIR)/obj/tests

DIRS = $(shell find . -type d -not -path "." -not -path "..")
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(PROJDIR)/tests/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
VPATH = $(SOURCEDIRS)
SOURCES = $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.cpp)) $(wildcard $(PROJDIR)/tests/*.cpp)

OBJ := $(subst $(PROJDIR)/tests,$(BUILDDIR), $(SOURCES:.cpp=.o))


define generateRules
$(1)/%.o: %.cpp
	$(CC) -c -o $$@ $$< $$(CFLAGS)
endef

$(BUILDDIR)/tests.o: $(PROJDIR)/tests/tests.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

VisualAlgoTest: $(OBJ) directories libVisualAlgo.a libCppUnitLite.a
	$(CC) -L../bin -L../CppUnitLite $(OBJ) -o ../bin/VisualAlgoTest -lVisualAlgo -lCppUnitLite $(OPTFLAGS)

libVisualAlgo.a:
	$(MAKE) -j -C ../src all

libCppUnitLite.a:
	$(MAKE) -j -C ../CppUnitLite libCppUnitLite.a

$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	mkdir -p $(TARGETDIRS)

all: directories libVisualAlgo.a libCppUnitLite.a VisualAlgoTest

clean:
	$(MAKE) -j -C ../src clean
	$(MAKE) -j -C ../CppUnitLite clean
	rm -rf $(TARGETDIRS)
	rm -f $(PROJDIR)/bin/VisualAlgoTest
	rm -f $(PROJDIR)/CppUnitLite/libCppUnitLite.a
	rm -f $(PROJDIR)/bin/libVisualAlgo.a
