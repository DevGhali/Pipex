# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 20:36:07 by gabd-el-          #+#    #+#              #
#    Updated: 2023/06/13 13:52:29 by gabd-el-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
GCC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = mandatory/pipex.c mandatory/pipex_utils.c mandatory/exec.c mandatory/pipex_utils2.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS	= bonus/pipex_bonus.c bonus/pipex_bonus_utils.c bonus/pipex_bonus_utils2.c bonus/here_doc.c
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

LIBFT_MAKE = make all -C libft
LIBFT_CP = cp libft/libft.a .

GNL_MAKE = make all -C get_next_line
GNL_CP = cp get_next_line/gnl.a .

RM = rm -f

all: $(NAME)

%.o: %.c
	$(GCC) -g -c $(CFLAGS) $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	${RM} $(BONUS_OBJS)
	$(LIBFT_MAKE)
	$(LIBFT_CP)
	$(GCC) $(FLAGS) -g -o $(NAME) $(OBJS) libft.a
	make clean

bonus: ${BONUS_OBJS}
	${RM} $(OBJS)
	$(LIBFT_MAKE)
	$(LIBFT_CP)
	$(GNL_MAKE)
	$(GNL_CP)
	$(GCC) $(FLAGS) -g -o $(NAME) $(BONUS_OBJS) libft.a gnl.a

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) libft.a gnl.a
	make fclean -C libft
	make fclean -C get_next_line

fclean:
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C get_next_line
	$(RM) libft.a
	$(RM) gnl.a
	make clean

re: fclean all

files:
	touch infile
	touch outfile

.PHONY: all clean fclean re files bonus