# ----------------------------------------------------------
# ---- ISO 8583 Library - Test Process ---------------------
# ----------------------------------------------------------

# Detect OS name
ifeq ($(OS),)
	OS := $(shell uname -s)
endif

# Tools setting
CC  := gcc
CXX := g++
LD  := g++
AR  := ar rcs

# Setting
OUTDIR  := .
ifeq ($(OS),Windows_NT)
	OUTPUT := $(OUTDIR)/libiso8583_test.exe
else
	OUTPUT := $(OUTDIR)/libiso8583_test
endif
TEMPDIR := temp
INCDIR  :=
INCDIR  += -I../include
INCDIR  += -I../3rd/genutil
LIBDIR  :=
LIBDIR  += -L../lib
CFLAGS  :=
CFLAGS  += -std=gnu++11
CFLAGS  += -Wall
CFLAGS  += -O0
CFLAGS  += -DISO8583_USE_STATICLIB
CFLAGS  += -DISO8583_DEBUGTEST
LDFLAGS :=
SRCS    :=
SRCS    += main.cpp
LIBS    :=
LIBS    += -liso8583_s
ifeq ($(OS),Linux)
    LIBS += -lrt
endif
OBJS    := $(notdir $(SRCS))
OBJS    := $(addprefix $(TEMPDIR)/,$(OBJS))
OBJS    := $(OBJS:%.c=%.o)
OBJS    := $(OBJS:%.cpp=%.o)
DEPS    := $(OBJS:%.o=%.d)

# Process summary
.PHONY: all clean
.PHONY: pre_step create_dir build_step post_step
.PHONY: install test
all: pre_step create_dir build_step post_step

# Clean process
clean:
ifeq ($(OS),Windows_NT)
	-del /Q $(subst /,\,$(OBJS))
	-del /Q $(subst /,\,$(DEPS))
	-del /Q $(subst /,\,$(OUTPUT))
	-rmdir /Q $(subst /,\,$(TEMPDIR))
else
	-@rm -f $(OBJS) $(DEPS) $(OUTPUT)
	-@rmdir $(TEMPDIR)
endif

# Build process

pre_step:
create_dir:
ifeq ($(OS),Windows_NT)
	@cmd /c if not exist $(subst /,\,$(TEMPDIR)) mkdir $(subst /,\,$(TEMPDIR))
	@cmd /c if not exist $(subst /,\,$(OUTDIR)) mkdir $(subst /,\,$(OUTDIR))
else
	@test -d $(TEMPDIR) || mkdir $(TEMPDIR)
	@test -d $(OUTDIR)  || mkdir $(OUTDIR)
endif
build_step: $(OUTPUT)
post_step:

$(OUTPUT): $(OBJS)
	$(LD) -o $@ $(LIBDIR) $(LDFLAGS) $^ $(LIBS)

define Compile-C-Unit
$(CC) -MM $(INCDIR) $(CFLAGS) -o $(TEMPDIR)/$*.d $< -MT $@
$(CC) -c  $(INCDIR) $(CFLAGS) -o $@ $<
endef
define Compile-Cpp-Unit
$(CXX) -MM $(INCDIR) $(CFLAGS) -o $(TEMPDIR)/$*.d $< -MT $@
$(CXX) -c  $(INCDIR) $(CFLAGS) -o $@ $<
endef

-include $(DEPS)
$(TEMPDIR)/%.o: %.c
	$(Compile-C-Unit)
$(TEMPDIR)/%.o: %.cpp
	$(Compile-Cpp-Unit)

# User extended process

install:

test: all
	./libiso8583_test
