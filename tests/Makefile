CC=g++

DEBUG ?= 1

ifeq ($(DEBUG),1)
   OPTFLAGS=-g
else
   OPTFLAGS=-O3
endif

CFLAGS=-I. -I../src -I../CppUnitLite -std=c++20 -Wall -Werror $(OPTFLAGS)

PROJDIR := $(realpath $(CURDIR)/..)
BUILDDIR := $(PROJDIR)/obj

DIRS = $(shell find . -type d)
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(PROJDIR)/tests/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
VPATH = $(SOURCEDIRS)
SOURCES = $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.cpp))

OBJ := $(subst $(PROJDIR)/tests,$(BUILDDIR), $(SOURCES:.cpp=.o))

define generateRules
$(1)/%.o: %.cpp
	$(CC) -c -o $$@ $$< $$(CFLAGS)
endef

VisualAlgoTest: $(OBJ) directories libVisualAlgo.a libCppUnitLite.a
	$(CC) -L../bin $(OBJ) -o ../bin/VisualAlgoTest -lVisualAlgo -lCppUnitLite $(OPTFLAGS)

libVisualAlgo.a:
	$(MAKE) -j -C ../src all

libCppUnitLite.a:
	$(MAKE) -j -C ../CppUnitLite all

$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	mkdir -p $(TARGETDIRS)

all: directories libVisualAlgo.a libCppUnitLite.a VisualAlgoTest

clean:
	$(MAKE) -j -C ../src clean
	$(MAKE) -j -C ../CppUnitLite clean
	rm -rf $(TARGETDIRS)
	rm -f $(PROJDIR)/bin/VisualAlgoTest
