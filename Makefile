TARGET = measure

OBJS = measure.o

LIBDIR = ../pktlib
LIB = $(LIBDIR)/libpkt.a

SRCS = $(OBJS:.o=.c)

CC ?= gcc

GFLAGS  = -O -Wall -g
CFLAGS  = -I$(LIBDIR)
LFLAGS  = -L$(LIBDIR) -lpkt

.SUFFIXES:
.SUFFIXES: .o .c

all :		$(TARGET)

.c.o :
		$(CC) $(GFLAGS) $(CFLAGS) -c $<

$(TARGET) :	$(OBJS) $(LIB)
		$(CC) $(OBJS) $(GFLAGS) $(LFLAGS) -o $@

$(LIB) :
		cd $(LIBDIR) ; $(MAKE)

clean :
		rm -f $(OBJS) $(TARGET)
