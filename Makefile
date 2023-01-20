# Makefile to compile the fdf project``

# to compile something wit a static library:
# 1. compile the main.c to main.o using cc main.c main.o the header has to be also included 
# 2. compile the .o file with the .a file using cc -o main main.o -L. lib.a

NAME = fdf

FILENAMES = main

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

INCLUDES_DIR = ./libft/includes/

.c.o: ${SRCS}
	cc -c $@ $< -I ${INCLUDES_DIR}

${NAME}: ${OBJS}
	cc -o fdf $^ -L. ./libft/libft.a

libft:
	make -C ./libft
