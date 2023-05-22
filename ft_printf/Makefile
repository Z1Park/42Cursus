# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:46:44 by jpark2            #+#    #+#              #
#    Updated: 2022/11/21 13:05:47 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar -rcs
LIBFT = ./libft/libft.a
SRCS = ft_printf.c print_variable1.c print_variable2.c lst_control.c
OBJS = $(SRCS:.c=.o)
B_SRCS = flag_control_bonus.c ft_printf_bonus.c put_char_bonus.c put_int_bonus.c \
		put_str_bonus.c common_bonus.c put_hex_bonus.c put_ptr_bonus.c \
		put_uint_bonus.c put_pcnt_bonus.c lst_control_bonus.c
B_OBJS = $(B_SRCS:.c=.o)

all: $(LIBFT) $(OBJS)
	$(RM) all bonus $(NAME)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)
	touch $@

bonus: $(LIBFT) $(B_OBJS)
	$(RM) all bonus $(NAME)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(B_OBJS)
	touch $@

clean :
	make -C $(dir $(LIBFT)) clean
	$(RM) all bonus $(OBJS) $(B_OBJS)

fclean : clean
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

$(LIBFT) :
	make -C $(dir $(LIBFT)) all

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean fclean re
