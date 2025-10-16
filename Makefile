CC      = clang
CFLAGS  = -std=c23 -g -Wall -Wextra -Wpedantic -Wshadow -Wstrict-prototypes -Wvla
RM      = rm -rf
OBJDIR  = build/
SRCDIR  = ray_tracing/
 
default: all

all: $(OBJDIR)main

$(OBJDIR)main: $(OBJDIR)vec3.o $(OBJDIR)colour.o $(OBJDIR)sphere.o $(OBJDIR)interval.o $(OBJDIR)ray.o $(OBJDIR)camera.o $(OBJDIR)helper.o
	$(CC) $(CFLAGS) -o $(OBJDIR)main $(SRCDIR)main.c $(OBJDIR)vec3.o $(OBJDIR)colour.o $(OBJDIR)sphere.o $(OBJDIR)interval.o $(OBJDIR)ray.o $(OBJDIR)camera.o $(OBJDIR)helper.o -lm

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

$(OBJDIR)camera.o: $(SRCDIR)camera.c $(SRCDIR)camera.h
	$(CC) $(CFLAGS) -c $(SRCDIR)camera.c -o $(OBJDIR)camera.o

$(OBJDIR)helper.o: $(SRCDIR)helper.c $(SRCDIR)helper.h
	$(CC) $(CFLAGS) -c $(SRCDIR)helper.c -o $(OBJDIR)helper.o
clean:
	$(RM) $(OBJDIR)main $(OBJDIR)ray.o $(OBJDIR)interval.o $(OBJDIR)colour.o $(OBJDIR)vec3.o $(OBJDIR)camera.o $(OBJDIR)sphere.o $(OBJDIR)helper.o $(OBJDIR)main.dSYM
