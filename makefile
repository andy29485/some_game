CC    = g++
OPTS  = -lm
OPTSR = -O3
OPTSD = -g -Wall

SRCDIR=./src
OBJDIR=./obj
INCDIR=./include
BINDIR=./bin

SRCS=$(SRCDIR)/main.c

INCLUDE = $(addprefix -I,$(INCDIR))
OBJS  = ${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}
CFLAGS  = $(OPTS) $(INCLUDE) $(DEBUG)

TARGET = $(BINDIR)/game

all: $(TARGET)

$(TARGET): $(OBJS) $(BIDIR)
	${CC} ${CFLAGS} -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

install:
	echo TODO

deb
	echo TODO

clean:
	rm -f $(OBJSDIR)/*.o

cleanall:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*
