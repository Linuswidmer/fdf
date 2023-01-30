# Makefile to compile the fdf project``

# to compile something wit a static library:
# 1. compile the main.c to main.o using cc main.c main.o the header has to be also included 
# 2. compile the .o file with the .a file using cc -o main main.o -L. lib.a

NAME = fdf

FILENAMES = main parse_map parse_map_utils window events draw rotation map

SRCS_DIR = ./sources_fdf/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))

OBJS_DIR = ./sources_fdf/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

CFLAGS = -Werror -Wall -Wextra
MINILIBXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

INCLUDES_DIR = -I ./libft/includes/ -I ./includes_fdf/ -I ./mlx_linux/

${NAME}: ${OBJS}
	cc -o fdf $^ -L. ./libft/libft.a $(MINILIBXFLAGS)

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $< ${INCLUDES_DIR} -Imlx_linux -O3

all: lib ${NAME} clean

lib:
	make -C ./libft/
	
mlx:
	wget https://projects.intra.42.fr/uploads/document/document/13502/minilibx-linux.tgz
	tar -xvzf minilibx-linux.tgz
	mv minilibx-linux mlx_linux
	rm minilibx-linux.tgz

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

memory:
	cc -g3 -fsanitize=address -Werror -Wall -Wextra ${SRCS} $(MINILIBXFLAGS) ${INCLUDES_DIR} -L. ./libft/libft.a -o fdf
