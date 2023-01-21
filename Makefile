# Makefile to compile the fdf project``

# to compile something wit a static library:
# 1. compile the main.c to main.o using cc main.c main.o the header has to be also included 
# 2. compile the .o file with the .a file using cc -o main main.o -L. lib.a

NAME = fdf

FILENAMES = main parse_map parse_map_utils

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

CFLAGS = -g3 -fsanitize=address

INCLUDES_DIR = -I ./libft/includes/ -I ./includes_fdf/

.c.o: ${SRCS}
	cc -c $@ $< ${INCLUDES_DIR}

${NAME}: ${OBJS}
	cc -o fdf $^ -L. ./libft/libft.a

memory:
	cc -Werror -Wall -Wextra -g3 -fsanitize=address ${SRCS} ${INCLUDES_DIR} -L. ./libft/libft.a -o fdf

libft:
	make -C ./libft
