# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 11:47:19 by jpark2            #+#    #+#              #
#    Updated: 2023/03/12 11:08:11 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
MLX_DIR = minilibx_opengl
MLX_LIB = minilibx_opengl/libmlx.a
MLX_INC = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm
LIBFT_DIR = libft
LIBFT = libft/libft.a
LIBFT_INC = -L$(LIBFT_DIR) -lft
GNL_DIR = get_next_line
SRCS = minirt.c file_parse.c color.c utils.c utils2.c \
	vector_operation.c vector_operation2.c \
	phong_lighting.c setting.c setting2.c object.c vector.c \
	sphere.c plane.c cylinder.c cone.c bump.c color_utils.c \
	ray_casting.c ray_hit.c shadow.c scatter.c \
	random_utils.c ray_utils.c texture.c control.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
B_SRCS = minirt_bonus.c file_parse_bonus.c color_bonus.c utils_bonus.c utils2_bonus.c \
	vector_operation_bonus.c vector_operation2_bonus.c \
	phong_lighting_bonus.c setting_bonus.c setting2_bonus.c object_bonus.c vector_bonus.c \
	sphere_bonus.c plane_bonus.c cylinder_bonus.c cone_bonus.c bump_bonus.c color_utils_bonus.c \
	ray_casting_bonus.c ray_hit_bonus.c shadow_bonus.c scatter_bonus.c \
	random_utils_bonus.c ray_utils_bonus.c texture_bonus.c control_bonus.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

ifdef BONUS
	F_OBJS = $(B_OBJS)
else
	F_OBJS = $(OBJS)
endif

all : $(NAME)

bonus:
	make BONUS=1 all

clean :
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) $(B_OBJS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

%.o:%.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -o $@ -c $<

$(NAME) : $(MLX_LIB) $(LIBFT) $(F_OBJS)
	$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) -o $@ $^

$(MLX_LIB) :
	make -C $(MLX_DIR) all

$(LIBFT) :
	make -C $(LIBFT_DIR) all

.PHONY : all clean fclean re bonus
