# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 11:47:31 by aarponen          #+#    #+#              #
#    Updated: 2023/11/11 19:39:02 by aarponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./Libft/

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
SRC_FILES = main.c parse.c exec.c error_and_exit.c
OBJ_DIR = obj
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))


all: $(NAME)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $^ -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY:	all clean fclean re