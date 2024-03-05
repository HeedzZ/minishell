# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 11:50:06 by ymostows          #+#    #+#              #
#    Updated: 2024/01/15 11:50:06 by ymostows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	cc

FLAG		=	-Wall -Werror -Wextra -g3

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

SRC		=	pipex2.c \
			error.c \
			free.c \
			here_doc.c \
			redirections.c

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	make -C $(LIBFT_PATH)

$(NAME): lib $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)

clean:
	make clean -sC $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
