# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 11:47:19 by jpark2            #+#    #+#              #
#    Updated: 2023/04/08 14:12:09 by heejikim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CXX = c++
CPPFLAGS = -std=c++98 -Wall -Wextra -Werror
RM = rm -rf
SRCS = ircserv.cpp Command.cpp User.cpp Channel.cpp Socket.cpp Server.cpp \
	message.cpp utils.cpp IrcLog.cpp
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
	$(CXX) $(CPPFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY : all clean fclean re bonus
