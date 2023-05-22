# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 08:13:33 by jpark2            #+#    #+#              #
#    Updated: 2023/01/24 18:25:02 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf
SRCS = get_args_bonus.c philo_action_bonus.c philo_bonus.c \
	philo_utils_bonus.c process_bonus.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

%.o:%.c
	$(CC) $(CFLAG) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $@ $^

.PHONY : all clean fclean re bonus
