# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:46:44 by jpark2            #+#    #+#              #
#    Updated: 2022/12/10 18:55:13 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar -rcs
LIBFT = libft/libft.a
SRCS = gnl.c gnl_utils.c file_parse.c pipeline.c pipeline_utils.c pipex.c \
	error_control.c str_parse.c cmd_retouch.c
OBJS = $(SRCS:.c=.o)
B_SRCS = gnl_bonus.c gnl_utils_bonus.c file_parse_bonus.c pipeline_bonus.c \
	pipeline_utils_bonus.c pipex_bonus.c error_control_bonus.c \
	str_parse_bonus.c cmd_retouch_bonus.c
B_OBJS = $(B_SRCS:.c=.o)

all: $(LIBFT) $(OBJS)
	$(RM) all bonus $(NAME)
	$(CC) $(CFLAGS) -o $(NAME) $^
	touch $@

bonus: $(LIBFT) $(B_OBJS)
	$(RM) all bonus $(NAME)
	$(CC) $(CFLAGS) -o $(NAME) $^
	touch $@

clean :
	make -C $(dir $(LIBFT)) clean
	$(RM) all bonus $(OBJS) $(B_OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

$(LIBFT) :
	make -C $(dir $(LIBFT)) all

.PHONY : clean fclean re
