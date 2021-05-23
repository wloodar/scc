# Copyright (C) 2021  bellrise

# This is the Makefile for compiling the SCC Toolkit. It provides 2 different
# targets, with one being the production build (default) and then the debug
# build which packs clang's sanitizers and compiles additional debug output
# along with the program.

# Note, this file is stolen from the svm Makefile. But because the process
# is so similar, pretty much everything can be stolen.

# Just use bash...

SHELL = /bin/bash


# Because this is a smaller project than the virtual itself, I just change
# the version numbers here. Instead of pulling them from a version.conf file
# using a Python script.

MAJOR := 0
MINOR := 1


# Stop users from executing internal targets.

$(if $(filter __%, $(MAKECMDGOALS)), $(error "Cannot use internal targets"))


# The target variable is set to the target system, linux for 64 bit
# Linux systems and win32 or win64 depending on the goal.

TARGET := linux
win32 : TARGET := win32
win64 : TARGET := win64


# This is the name of the binary that will be created as the result.

RESULT = scc


# Root folder of the makefile. Used in operations which require directory
# changing. a cd to $(ROOT) will always return you to the initial area,
# where the Makefile is located.

ROOT = $(abspath .)


# This makefile supports both gcc and clang, so probably 99% of the used
# compilers (in the Linux world, I know there is msvc). It's set to use
# clang by default, because it has a lot of cool stuff like sanitizers
# that really help in debug builds of scc. If you don't have clang and
# just want to compile using gcc, pass it as a parameter in the make
# command, like so: `make CC=gcc`.

CC = clang


# Windows compilers.

win32 : CC := i686-w64-mingw32-gcc
win64 : CC := x86_64-w64-mingw32-gcc


# Include path for the SCC headers. Because we'll need some headers from
# the svm include library, I add that too.

INCLUDE_FLAGS = -I$(ROOT)/include -I$(ROOT)/../include


# The default CFLAGS are all set to all warnings, and the newest C version.

CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-command-line-argument -std=c2x \
		 -O3 -Wno-unused-result -ldl -Wno-pointer-arith -Wno-unused-parameter


# DEBUG is defined it the debug target is selected. Additionally, if the
# compiler is clang, the sanitizer parameters are strapped onto the executable.

debug : CFLAGS += -D DEBUG -pg -O1
debug : RESULT := scc

ifeq ($(CC), clang)
debug : CFLAGS += -fsanitize=address -fno-omit-frame-pointer \
		          -fno-optimize-sibling-calls
endif


# These are the sources and object paths which are just fetched using some
# good old bash commands. The src/ prefix is removed from the path to only
# get the code.c path, and then the newlines are removed to move it into
# one line. The objects are also listed here, adding build/objects and
# and a .o suffix.

SOURCES := $(shell find src -name \*.c | sed 's/src\///' | tr '\n' ' ')
OBJECTS := $(foreach var,$(SOURCES),build/objects/$(var).o)


# -----------------------------------------------------------------------------
# Internal targets
# -----------------------------------------------------------------------------

# The default target. This compiles and links the objects for a general
# Linux 64 bit executable. Use this target if you just want to build and
# get on with your life. Imporant note: this target has to be the first target,
# because it is the default one.

__all: __setup $(SOURCES) __link
.PHONY : __all


# The help target will list all current possible targets. Use this when you
# don't know which target to use for your goal.

help:
	printf "\
	SCC build system. To use one of these targets, just use 'make TARGETNAME'\n\n\
	It is highly recommended to use clang instead of gcc, because of the additional\n\
	functionality & static checking it provides. This Makefile is built around \n\
	clang, but gcc is also supported\n\n\
	Targets:\n\n\
		[default] 	build the production version of SCC, for Linux\n\
		debug		build the debug version for Linux\n\
		win32		build for Windows 32-bit, requires mingw-gcc\n\
		win64 		build for Windows 64-bit, requires mingw-gcc\n\
		help		show this page and exit\n\
		install		install the built binaries in ~/bin\n\
		clean		clean the build directory\n\
	\n\
	Variables:\n\n\
		CC		the compiler used\n\
		MAIN		.c file with the main fucntion\n\
		RESULT 		name of the built result\n\
		MAKE_CFLAGS 	additional flags for compilation\n\
		MAKE_DEBUG	if this is set to 1, print debug information\n\
	\n"
	exit 0

.PHONY  : help
# Make help always silent, even if you specify the debug version.
.SILENT : help


# The clean target removes the build directory where all object files stay.

clean:
	@echo "Cleaning build directory"
	@rm -rf build
.PHONY : clean


# The installation target. This installs the compiled executable into the
# users' ~/bin directory.

install:
	echo "Checking for built executable"
	if [ -x "build/$(RESULT)" ]; then \
		echo "Found executable"; \
		if [ -d "$(HOME)/bin" ]; then \
			echo "Found bin/ directory, moving binary."; \
			mv build/$(RESULT) $(HOME)/bin/$(RESULT); \
		else \
			echo "Cannot find $(HOME)/bin directory"; \
		fi \
	fi

.PHONY : install
ifneq ($(MAKE_DEBUG), 1)
.SILENT : install
endif


# -----------------------------------------------------------------------------
# Internal subroutines
# -----------------------------------------------------------------------------

# The setup target is called before every compilation target. It is
# responsible for creating directories and cleaning unwated old files.
# We also want to steal the all the required dependencies from SVM.

__setup:
	printf "Building SCC toolkit $(MAJOR).$(MINOR) for $(TARGET) [$(CC)]\n"

	if [ "${MAKE_CFLAGS}" != "" ]; then \
		echo "Using enviromental MAKE_CFLAGS = ${MAKE_CFLAGS}"; \
	fi

	echo "Creating directories"
	mkdir -p build
	mkdir -p build/objects

	echo "Stealing source code from SVM"
	cp $(ROOT)/../src/string.c $(ROOT)/src/string.c
	cp $(ROOT)/../src/safety.c $(ROOT)/src/safety.c
	cp $(ROOT)/../src/debug.c $(ROOT)/src/debug.c

.PHONY  : __setup
ifneq ($(MAKE_DEBUG), 1)
.SILENT : __setup
endif


# The compile target is called compiling the source files into object files.
# All objects are saved in build/objects, which then are linked in __link.
# Note: if the MAKE_CFLAGS enviroment variable is defined, it will be placed
# at the end of the compilation instruction.

$(SOURCES):
	echo "Compiling $@"
	$(CC) $(CFLAGS) -D SCC_VERSION=\"$(MAJOR).$(MINOR)\" $(INCLUDE_FLAGS) \
		${MAKE_CFLAGS} -c -o build/objects/$@.o src/$@

ifneq ($(MAKE_DEBUG), 1)
.SILENT : $(SOURCES)
endif


# The link target is the final step in compilation. Note: if the MAKE_CFLAGS
# enviroment variable is defined, it will be placed at the end of the linking
# instruction.

__link:
	echo "Linking objects with main"
	$(CC) $(CFLAGS) -D SCC_VERSION=\"$(VERSION)\" $(INCLUDE_FLAGS) \
		-o build/$(RESULT) ${MAKE_CFLAGS} $(OBJECTS)
	printf "\e[92mDone\e[0m\n"

ifneq ($(MAKE_DEBUG), 1)
.SILENT : __link
endif


# -----------------------------------------------------------------------------
# Non-default targets
# -----------------------------------------------------------------------------

# The debug target is used, well, for debugging purposes. The way this works is
# it compiles the program like usual, but with DEBUG defined, so all #ifdef DEBUG
# headers evaluate to true.

debug: __setup $(SOURCES) __link
	@echo "Built debug"
.PHONY : debug

# The windows scripts are similar, they just use diffrent compilers.

win32: __setup $(SOURCES) __link
	@echo "Built for Windows 32 bit"
.PHONY : win32

win64: __setup $(SOURCES) __link
	@echo "Built for Windows 64 bit"
.PHONY : win64
