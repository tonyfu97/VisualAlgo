CC=g++

DEBUG ?= 1

ifeq ($(DEBUG),1)
   OPTFLAGS=-g
else
   OPTFLAGS=-O3
endif

CFLAGS=-I. -std=c++20 -Wall -Werror $(OPTFLAGS) $(shell pkg-config --cflags opencv4)

PROJDIR := $(realpath $(CURDIR)/..)
BUILDDIR := $(PROJDIR)obj/src
CPPUNITLITE_DIR := $(PROJDIR)/CppUnitLite

DIRS = $(shell find . -type d -not -path "." -not -path "..")
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(PROJDIR)/src/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))
VPATH = $(SOURCEDIRS)
SOURCES = $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.cpp))

OBJ := $(subst $(PROJDIR)/src,$(BUILDDIR), $(SOURCES:.cpp=.o))

define generateRules
$(1)/%.o: %.cpp
	$(CC) -c -o $$@ $$< $$(CFLAGS)
endef

libVisualAlgo.a: $(OBJ)
	ar rcs $(PROJDIR)/bin/libVisualAlgo.a $(OBJ)
	ranlib $(PROJDIR)/bin/libVisualAlgo.a

libCppUnitLite.a:
	$(MAKE) -j -C $(CPPUNITLITE_DIR) all

all: directories libVisualAlgo.a libCppUnitLite.a

clean:
	rm -rf $(TARGETDIRS)
	rm -f $(PROJDIR)/bin/libVisualAlgo.a
	$(MAKE) -j -C $(CPPUNITLITE_DIR) clean

$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories:
	mkdir -p $(TARGETDIRS)
