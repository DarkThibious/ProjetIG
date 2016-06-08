INCPATH = -I /usr/local/include -I /usr/X11R6/include -I./src
LIBPATH = -L /usr/local/lib -L /usr/X11R6/lib
LIBRARY = -lglut -lGLU -lGL -lX11 -lXext -lXi -lXmu -lm -ljpeg -lpng

CFLAGS = $(INCPATH)
LDFLAGS = $(LIBPATH) $(LIBRARY)
EXEC = avatar
GCC = /usr/bin/gcc
SRC = main.c init.c	anim.c disp.c formes.c
HDRS = init.h anim.h disp.h formes.h
OBJS = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS) 
	$(GCC) $(LDFLAGS) -o $(EXEC) $^ -Wall 

%.o: %.c $(HDRS)
	$(GCC) $(CFLAGS) -o $@ -c $< -Wall

# cette commande permet de supprimer tous les objets
clean:
	@rm *.o $(EXEC)

