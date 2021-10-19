NAME = fdf

CC = gcc -g
CFLAGS = -c #-Werror -Wall -Wextra
LFLAGS = -L srcs/minilibx -lmlx -lXext -lX11 -lm -lbsd

FILES = srcs/main.c srcs/events.c srcs/utils.c srcs/utils2.c srcs/read_map.c srcs/draw.c srcs/algorithm.c srcs/rgb.c\
		srcs/GNL/get_next_line.c srcs/GNL/get_next_line_utils.c
OBJ = obj/*.o

all: $(NAME)

$(NAME): $(FILES)
	$(CC) $(CFLAGS) $(FILES)
	mkdir -p obj
	mv *.o obj
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

clean :
	rm -f *.o
	rm -f obj/*.o

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re