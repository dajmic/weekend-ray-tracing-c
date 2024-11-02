CC      = gcc
CFLAGS  = -g
RM      = rm -rf
OBJDIR  = build/
SRCDIR  = ray_tracing/

default: all

all: $(OBJDIR)main

$(OBJDIR)main: $(OBJDIR)hit_record.o $(OBJDIR)sphere.o $(OBJDIR)ray.o $(OBJDIR)colour.o $(OBJDIR)vec3.o 
	$(CC) $(CFLAGS) -o $(OBJDIR)main $(SRCDIR)main.c $(OBJDIR)hit_record.o $(OBJDIR)sphere.o $(OBJDIR)ray.o $(OBJDIR)colour.o $(OBJDIR)vec3.o  -lm

$(OBJDIR)ray.o: $(SRCDIR)ray.c $(SRCDIR)ray.h
	$(CC) $(CFLAGS) -c $(SRCDIR)ray.c -o $(OBJDIR)ray.o

$(OBJDIR)colour.o: $(SRCDIR)colour.c $(SRCDIR)colour.h
	$(CC) $(CFLAGS) -c $(SRCDIR)colour.c -o $(OBJDIR)colour.o

$(OBJDIR)vec3.o: $(SRCDIR)vec3.c $(SRCDIR)vec3.h
	$(CC) $(CFLAGS) -c $(SRCDIR)vec3.c -o $(OBJDIR)vec3.o

$(OBJDIR)sphere.o: $(SRCDIR)sphere.h $(SRCDIR)sphere.c
	$(CC) $(CFLAGS) -c $(SRCDIR)sphere.c -o $(OBJDIR)sphere.o

$(OBJDIR)hit_record.o: $(SRCDIR)hit_record.h $(SRCDIR)hit_record.c
	$(CC) $(CFLAGS) -c $(SRCDIR)hit_record.c -o $(OBJDIR)hit_record.o

clean:
	$(RM) $(OBJDIR)main $(OBJDIR)ray.o $(OBJDIR)colour.o $(OBJDIR)vec3.o $(OBJDIR)hit_record.o $(OBJDIR)sphere.o $(OBJDIR)main.dSYM