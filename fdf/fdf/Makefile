# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 16:47:17 by jpark2            #+#    #+#              #
#    Updated: 2022/12/05 17:03:16 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAG = -Wall -Wextra -Werror
MLX_FLAG = -lmlx -framework OpenGL -framework Appkit -lm
AR = ar -rsc
RM = rm -f
SRCS = common.c coordinate.c error_control.c fdf.c file_parse.c ft_atoi.c ft_split.c rotate.c \
	get_next_line.c get_next_line_utils.c hook_control.c image.c image_utils.c mlx_control.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : 
	make fclean
	make all

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(MLX_FLAG) -o $@ $^

.PHONY : all clean fclean re bonus
