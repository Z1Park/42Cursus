# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 08:13:33 by jpark2            #+#    #+#              #
#    Updated: 2022/12/22 11:36:56 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf
SRCS = get_args.c philo.c philo_action.c philo_utils.c pthread.c fork_ctrl.c
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
