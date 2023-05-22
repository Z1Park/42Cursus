# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 19:50:21 by jpark2            #+#    #+#              #
#    Updated: 2023/01/05 10:19:16 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_LBLUE		= \033[0;94m
COLOR_YELLOW	= \033[0;33m
COLOR_MAGENTA	= \033[0;35m
COLOR_WHITE		= \033[0;0m

COUNT = 0

NAME = libft.a
INC_DIR = ../include
CC = cc
CFLAG = -Wall -Wextra -Werror -I$(INC_DIR)
AR = ar -rsc
RM = rm -rf
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_substr.c \
		ft_strdup.c ft_strdup_uc.c ft_strndup.c ft_strndup_uc.c \
		ft_strjoin.c ft_strjoin_uc.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_strcmp.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
		ft_lstnew.c ft_lstsize.c
OBJS_NAME = $(SRCS:.c=.o)
OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

all : $(NAME)

clean :
	@$(RM) $(OBJS_DIR)
	@echo "$(NAME): $(COLOR_RED)object files are deleted$(COLOR_WHITE)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(COLOR_RED)deleted!$(COLOR_WHITE)"

re :
	@make fclean
	@make all

$(NAME) : $(OBJS_DIR) $(OBJS)
	@$(AR) $@ $(OBJS)
	@echo "\n$(COLOR_WHITE)$(NAME): $(COLOR_GREEN)created!$(COLOR_WHITE)"

$(OBJS_DIR) :
	@mkdir $(OBJS_DIR)

$(OBJS_DIR)%.o : %.c
	@$(CC) $(CFLAG) -c $< -o $@
	$(eval COUNT=$(shell find $(OBJS_DIR) -name "*.o" | wc -l))
	@echo "\r$(COLOR_WHITE)$(NAME): $(COLOR_YELLOW)$(COUNT) object files are created\c"

.PHONY : all clean fclean re bonus
