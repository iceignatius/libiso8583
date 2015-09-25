# ----------------------------------------------------------
# ---- ISO 8583 Library ------------------------------------
# ----------------------------------------------------------

# Detect OS name
ifeq ($(OS),)
	OS := $(shell uname -s)
endif

# Tools setting
CC  := gcc
CXX := g++
LD  := gcc
AR  := ar rcs

# Path setting
ifndef INSTDIR
	INSTDIR = /usr/local
endif

# Processes

.PHONY: all clean install uninstall test doc

all:
	cd lib && $(MAKE) -f makefile-static $(MAKECMDGOALS)
	cd lib && $(MAKE) -f makefile-shared $(MAKECMDGOALS)

clean:
	cd lib  && $(MAKE) -f makefile-static $(MAKECMDGOALS)
	cd lib  && $(MAKE) -f makefile-shared $(MAKECMDGOALS)
	cd test && $(MAKE) -f makefile        $(MAKECMDGOALS)
	cd doc  && $(MAKE) -f makefile        $(MAKECMDGOALS)

install:
	cd lib && $(MAKE) -f makefile-static $(MAKECMDGOALS)
	cd lib && $(MAKE) -f makefile-shared $(MAKECMDGOALS)
ifneq ($(OS),Windows_NT)
	test -d $(INSTDIR)/include/iso8583 || mkdir $(INSTDIR)/include/iso8583
	cp include/iso8583/*  $(INSTDIR)/include/iso8583
	cp lib/libiso8583_s.a $(INSTDIR)/lib
	cp lib/libiso8583.so  $(INSTDIR)/lib
endif

uninstall:
ifneq ($(OS),Windows_NT)
	-rm $(INSTDIR)/lib/libiso8583.so
	-rm $(INSTDIR)/lib/libiso8583_s.a
	-rm $(INSTDIR)/include/iso8583/*
	-rmdir $(INSTDIR)/include/iso8583
endif

test: all
	cd test && $(MAKE) -f makefile $(MAKECMDGOALS)

doc:
	cd doc && $(MAKE) -f makefile $(MAKECMDGOALS)
