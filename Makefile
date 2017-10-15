#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 16:47:54 by tshevchu          #+#    #+#              #
#    Updated: 2017/10/15 15:23:12 by tshevchu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/

LIBMLX = minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

OBJECTS = additional2.o additional_func.o bresenham.o calculate.o key_processing.o main.o make_fdf_colorful.o structs.o validation.o

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT)
	@gcc $(OBJECTS) $(FLAGS) $(LIBFT)libft.a $(LIBMLX) -o $(NAME)
	@echo "\x1B[01;34m>>>>>FDF IS READY!!<<<<<"

%.o: ./%.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -f $(OBJECTS)
	@echo "\x1B[01;90m>>>CLEAN FDF & LIBFT OBJ<<<"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\x1B[01;93m>>>EVERYTHING IS CLEAR:)<<<"

re: fclean all