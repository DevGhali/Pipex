# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 20:36:07 by gabd-el-          #+#    #+#              #
#    Updated: 2023/03/18 21:12:35 by gabd-el-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
GCC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = pipex.c pipex_utils.c exec.c
OBJS = $(SRCS:.c=.o)

LIBFT_MAKE = make all -C ./libft
LIBFT_CP = cp ./libft/libft.a .

RM = rm -f

all: $(NAME)

.c.o: $(SRCS)
	$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(LIBFT_MAKE)
	$(LIBFT_CP)
	$(GCC) $(FLAGS) -o $(NAME) $(OBJS) libft.a
	
clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./libft
	$(RM) libft.a
	$(RM) infile outfile

re: fclean all

files:
	touch infile
	touch outfile

.PHONY: all clean fclean re files