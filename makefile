#compiling locations
SRCDIR=./src
OBJDIR=./obj
INCDIR=./include
BINDIR=./bin

#Installing
DESTDIR          = /
INSTALL_LOCATION = $(DESTDIR)/usr/
NAME             = game

#comiler options
CC       = g++
OPTS     = -lm
OPTSR    = -O3
OPTSD    = -g -Wall
INCLUDE := $(addprefix -I,$(INCDIR))
CFLAGS  := $(OPTS) $(INCLUDE) $(DEBUG) $(shell dpkg-buildflags --get CFLAGS)  
LDFLAGS := $(shell dpkg-buildflags --get LDFLAGS)

SRCS     = $(SRCDIR)/main.c
OBJS     = ${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}

TARGET   = $(BINDIR)/$(NAME)

all: $(TARGET)

$(TARGET): $(OBJS) $(BIDIR)
	${CC} ${CFLAGS} -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

install: install_exec_linux

install_exec_linux:
	mkdir -p $(INSTALL_LOCATION)/bin
	cp $(TARGET) $(INSTALL_LOCATION)/bin
	chmod 755 $(INSTALL_LOCATION)/bin/$(NAME)

deb
	echo TODO

clean:
	rm -f $(OBJSDIR)/*.o

cleanall:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*
