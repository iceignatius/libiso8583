# ----------------------------------------------------------
# ---- ISO 8583 Library - Document -------------------------
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
ifndef DESTDIR
	DESTDIR = /usr/local
endif

# Processes

.PHONY: all clean install uninstall test doc

all:
	cd .. && doxygen
ifneq ($(OS),Windows_NT)
	sed -i -e 's,begin{document},usepackage{CJKutf8}\n\\begin{document}\n\\begin{CJK}{UTF8}{bsmi},' latex/refman.tex
	sed -i -e 's,end{document},end{CJK}\n\\end{document},' latex/refman.tex
	cd latex/ && make pdf
	cp latex/refman.pdf ISO8583_Library_Document.pdf
endif

clean:
ifeq ($(OS),Windows_NT)
	del /F /Q /S html
	del /F /Q /S latex
	del /F /Q /S *.pdf
else
	-rm -r html latex *.pdf
endif

install: all

uninstall:

test: all

doc: all
