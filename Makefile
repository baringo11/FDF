# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 13:31:43 by jbaringo          #+#    #+#              #
#    Updated: 2021/10/20 13:32:08 by jbaringo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Werror -Wall -Wextra
LFLAGS = -L srcs/minilibx -lmlx -lXext -lX11 -lm -lbsd

FILES = srcs/main.c srcs/events.c srcs/utils.c srcs/utils2.c srcs/read_map.c srcs/draw.c srcs/algorithm.c srcs/rgb.c\
		srcs/GNL/get_next_line.c srcs/GNL/get_next_line_utils.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LFLAGS)

clean :
	rm -f *.o
	rm -rf obj

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
