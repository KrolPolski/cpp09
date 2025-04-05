# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 10:35:46 by rboudwin          #+#    #+#              #
#    Updated: 2025/04/05 14:07:26 by rboudwin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= PmergeMe
CFLAGS  := -Wall -Wextra -Werror -std=c++20 -fsanitize=address
SRCS	:= main.cpp PmergeMe.cpp
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