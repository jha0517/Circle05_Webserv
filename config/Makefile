# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 13:55:40 by yhwang            #+#    #+#              #
#    Updated: 2023/03/20 04:20:37 by yhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse_test
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
RM = rm -f

FILES = ./srcs/main \
		./srcs/Parse \
		./srcs/HttpBlockParse \
		./srcs/ParseUtils

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

INCS_DIR = ./incs/

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -I$(INCS_DIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re