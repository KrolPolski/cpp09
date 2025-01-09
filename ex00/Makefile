# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/31 15:45:02 by rboudwin          #+#    #+#              #
#    Updated: 2025/01/09 12:10:33 by rboudwin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= btc
CFLAGS  := -Wextra -Wall -Werror -std=c++11 -fsanitize=address
SRCS	:= main.cpp BitcoinExchange.cpp
OBJS	:= ${SRCS:.cpp=.o}

all: $(NAME)

%.o: %.cpp
	@c++ $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@c++ $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean all

.PHONY: all, clean, fclean, re