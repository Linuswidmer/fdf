#Makefile to comile a test program with the minilibx library

SRCS = key_handling.c
OBJ = key_handling.o
NAME = test


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

memory:
	cc -g3 -fsanitize=address ${SRCS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -I ./mlx_linux/ -o test
