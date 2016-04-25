INCPATH = -I /usr/local/include -I /usr/X11R6/include -I./src
LIBPATH = -L /usr/local/lib -L /usr/X11R6/lib
LIBRARY = -lglut -lGLU -lGL -lX11 -lXext -lXi -lXmu -lm -ljpeg -lpng

CFLAGS = $(INCPATH)
LDFLAGS = $(LIBPATH) $(LIBRARY)
EXEC = avatar
GCC = /usr/bin/gcc
SRC = main.c init.c	anim.c disp.c
OBJS = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(LDFLAGS) -o $(EXEC) $^ 

%.o: %.c
	$(GCC) $(CFLAGS) -o $@ -c $<

# cette commande permet de supprimer tous les objets
clean:
	@rm *.o $(EXEC)

