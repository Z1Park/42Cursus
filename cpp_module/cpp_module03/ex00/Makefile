# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 11:47:19 by jpark2            #+#    #+#              #
#    Updated: 2023/01/16 17:49:12 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex00
CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf
SRCS = main.cpp ClapTrap.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

%.o:%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^

.PHONY : all clean fclean re bonus
