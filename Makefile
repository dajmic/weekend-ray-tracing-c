
CC      = gcc
CFLAGS  = -g
RM      = rm -rf
OBJDIR  = build/
SRCDIR  = ray_tracing/
 
default: all

all: $(OBJDIR)main

$(OBJDIR)main: $(OBJDIR)vec3.o $(OBJDIR)colour.o $(OBJDIR)sphere.o $(OBJDIR)interval.o $(OBJDIR)ray.o 
	$(CC) $(CFLAGS) -o $(OBJDIR)main $(SRCDIR)main.c $(OBJDIR)vec3.o $(OBJDIR)colour.o $(OBJDIR)sphere.o $(OBJDIR)interval.o $(OBJDIR)ray.o -lm

$(OBJDIR)vec3.o: $(SRCDIR)vec3.c $(SRCDIR)vec3.h
	$(CC) $(CFLAGS) -c $(SRCDIR)vec3.c -o $(OBJDIR)vec3.o

$(OBJDIR)colour.o: $(SRCDIR)colour.c $(SRCDIR)colour.h
	$(CC) $(CFLAGS) -c $(SRCDIR)colour.c -o $(OBJDIR)colour.o

$(OBJDIR)sphere.o: $(SRCDIR)sphere.h $(SRCDIR)sphere.c
	$(CC) $(CFLAGS) -c $(SRCDIR)sphere.c -o $(OBJDIR)sphere.o

$(OBJDIR)interval.o: $(SRCDIR)interval.c $(SRCDIR)interval.h
	$(CC) $(CFLAGS) -c $(SRCDIR)interval.c -o $(OBJDIR)interval.o

$(OBJDIR)ray.o: $(SRCDIR)ray.c $(SRCDIR)ray.h
	$(CC) $(CFLAGS) -c $(SRCDIR)ray.c -o $(OBJDIR)ray.o

clean:
	$(RM) $(OBJDIR)main $(OBJDIR)ray.o $(OBJDIR)interval.o $(OBJDIR)colour.o $(OBJDIR)vec3.o $(OBJDIR)sphere.o $(OBJDIR)main.dSYM