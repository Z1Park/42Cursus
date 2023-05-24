# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 20:50:13 by jpark2            #+#    #+#              #
#    Updated: 2022/12/02 10:17:43 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
B_NAME = checker
CC = cc
CFLAG = -Wall -Wextra -Werror
AR = ar -rsc
RM = rm -f
SRCS = arg_parse.c common.c deque.c deque_sorting.c deque_utils.c ft_split.c \
	greedy.c libft_utils.c pushswap.c push_and_swap.c rotate.c
OBJS = $(SRCS:.c=.o)
B_SRCS = bonus/arg_parse_bonus.c bonus/deque_bonus.c bonus/deque_utils_bonus.c \
	bonus/libft_utils_bonus.c bonus/pushswap_bonus.c bonus/push_and_swap_bonus.c \
	bonus/rotate_bonus.c bonus/ft_split_bonus.c
B_OBJS = $(B_SRCS:.c=.o)

all : $(NAME)

bonus : $(B_NAME)

clean :
	$(RM) $(OBJS) $(B_OBJS)

fclean : clean
	$(RM) $(NAME) $(B_NAME)

re : 
	make fclean
	make all

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $@ $^

$(B_NAME) : $(B_OBJS)
	$(CC) $(CFLAG) -o $@ $^

.PHONY : all clean fclean re bonus
