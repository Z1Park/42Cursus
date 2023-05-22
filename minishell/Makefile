# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 19:03:36 by jpark2            #+#    #+#              #
#    Updated: 2023/01/06 22:12:25 by jpark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_RED		= \033[0;31m
COLOR_GREEN		= \033[0;32m
COLOR_LBLUE		= \033[0;94m
COLOR_YELLOW	= \033[0;33m
COLOR_MAGENTA	= \033[0;35m
COLOR_WHITE		= \033[0;0m

COUNT = 0

LIB_DIR=libft
INC_DIR = include
NAME = minishell
LIB = libft/libft.a
CC = cc
CFLAG = -Wall -Wextra -Werror -I$(INC_DIR)
RL_LINK_FLAG =  -lreadline -L${HOME}/.brew/opt/readline/lib/
RL_COMP_FLAG = -I${HOME}/.brew/opt/readline/include/
RM = rm -rf
SRCS = builtins/builtins_exit.c builtins/builtins_export.c \
	builtins/builtins_others.c builtins/builtins_unset.c \
	builtins/builtins_utils.c builtins/builtins_cd.c builtins/builtins_env.c\
	tokenizer/tokenizer.c tokenizer/tokenizer_utils.c \
	tokenizer/tokenizer_counter.c tokenizer/tokenizer_parser.c \
	tokenizer/tokenizer_infile.c tokenizer/tokenizer_outfile.c tokenizer/string_utils.c \
	tokenizer/tokenizer_heredoc.c tokenizer/tokenizer_heredoc_utils.c \
	tokenizer/wildcard.c tokenizer/wildcard_utils.c tokenizer/tokenizer_links.c \
	tokenizer/tokenizer_parenthesis.c \
	syntax/syntax_checker.c syntax/syntax_supporter.c \
	pipe/pipe.c pipe/pipe_utils.c pipe/pipe_restore.c \
	memory_manager.c signals.c terms.c common_utils.c env_utils.c \
	error_control.c minishell.c ft_readline.c print_logo.c
B_SRCS = builtins/builtins_exit_bonus.c builtins/builtins_export_bonus.c \
	builtins/builtins_others_bonus.c builtins/builtins_unset_bonus.c \
	builtins/builtins_utils_bonus.c builtins/builtins_cd_bonus.c builtins/builtins_env_bonus.c\
	tokenizer/tokenizer_bonus.c tokenizer/tokenizer_utils_bonus.c \
	tokenizer/tokenizer_counter_bonus.c tokenizer/tokenizer_parser_bonus.c \
	tokenizer/tokenizer_infile_bonus.c tokenizer/tokenizer_outfile_bonus.c tokenizer/string_utils_bonus.c \
	tokenizer/tokenizer_heredoc_bonus.c tokenizer/tokenizer_heredoc_utils_bonus.c \
	tokenizer/wildcard_bonus.c tokenizer/wildcard_utils_bonus.c tokenizer/tokenizer_links_bonus.c \
	tokenizer/tokenizer_parenthesis_bonus.c \
	syntax/syntax_checker_bonus.c syntax/syntax_supporter_bonus.c \
	pipe/pipe_bonus.c pipe/pipe_utils_bonus.c pipe/pipe_restore_bonus.c \
	memory_manager_bonus.c signals_bonus.c terms_bonus.c common_utils_bonus.c env_utils_bonus.c \
	error_control_bonus.c minishell_bonus.c ft_readline_bonus.c print_logo_bonus.c
OBJS_NAME = $(SRCS:.c=.o)
OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
B_OBJS_NAME = $(B_SRCS:.c=.o)
B_OBJS = $(addprefix $(OBJS_DIR), $(B_OBJS_NAME))

ifdef BONUS
	F_OBJS = $(B_OBJS)
else
	F_OBJS = $(OBJS)
endif

all : $(LIB) $(NAME)

bonus :
	make BONUS=1

clean :
	@make -C $(LIB_DIR) clean
	@$(RM) $(OBJS_DIR)
	@echo "$(NAME): $(COLOR_RED)object files are deleted$(COLOR_WHITE)"

fclean : clean
	@$(RM) $(LIB)
	@echo "$(LIB): $(COLOR_RED)deleted!$(COLOR_WHITE)"
	@$(RM) $(NAME)
	@echo "$(NAME): $(COLOR_RED)deleted!$(COLOR_WHITE)"

re :
	@make fclean
	@echo "$(COLOR_MAGENTA)==============================================$(COLOR_WHITE)"
	@make all

$(OBJS_DIR)%.o : %.c
	@$(CC) $(CFLAG) $(RL_COMP_FLAG) -c $< -o $@
	$(eval COUNT=$(shell find $(OBJS_DIR) -name "*.o" | wc -l))
	@echo "\r$(COLOR_WHITE)$(NAME): $(COLOR_YELLOW)$(COUNT) object files are created\c"

$(NAME) : $(OBJS_DIR) $(LIB) $(F_OBJS)
	@$(CC) $(CFLAG) $(RL_LINK_FLAG) -o $@ $(LIB) $(F_OBJS)
	@echo "\n$(COLOR_WHITE)$(NAME): $(COLOR_GREEN)created!$(COLOR_WHITE)"
	@echo "$(COLOR_LBLUE)==============================================$(COLOR_WHITE)"

$(OBJS_DIR) :
	@mkdir $(OBJS_DIR)
	@mkdir $(OBJS_DIR)builtins
	@mkdir $(OBJS_DIR)tokenizer
	@mkdir $(OBJS_DIR)syntax
	@mkdir $(OBJS_DIR)pipe

$(LIB) :
	@make -C $(LIB_DIR) all

.PHONY : all clean fclean re bonus
