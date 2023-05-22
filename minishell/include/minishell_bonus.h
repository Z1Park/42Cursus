/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:48:33 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/07 12:35:57 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_bonus.h"

# define HASH_MAX 64
# define BUF_MAX 1024
# define READ 0
# define WRITE 1
# define TRUE 1
# define FALSE 0
# define COLLECTIBLE 0
# define UNCOLLECTIBLE 1
# define IDLE 0
# define READING 1
# define HEREDOC 2

typedef enum e_error
{
	ERR_NONE,
	ERR_NOT_ENOUGH_ARGS,
	ERR_TOO_MANY_ARGS,
	ERR_INVALID_PARAM,
	ERR_NUM_ARG_REQ,
	ERR_NO_FILE,
	ERR_AUTH_FAIL,
	ERR_NO_CMD,
	ERR_MALLOC,
	ERR_CHDIR,
	ERR_GET_CWD,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP,
	ERR_WAITPID,
	ERR_EXE_FAIL,
	ERR_ENV_PATH,
	ERR_OPENDIR,
	ERR_AMBIGUOUS_REDIRECT,
	ERR_SYNTAX,
	ERR_NO_OLDPWD,
	ERR_NO_HOME,
}	t_error;

typedef enum e_exit_code
{
	EXIT_NO_ERR			= 0,
	EXIT_NORMAL_ERR		= 1,
	EXIT_CMD_NOT_FOUND	= 127,
	EXIT_OUT_OF_RANGE	= 255,
}	t_exit_code;

typedef enum e_token_res
{
	TOKEN_SUCCESS	= 0,
	TOKEN_RD_FAIL	= 1,
	TOKEN_WR_FAIL	= 2,
	TOKEN_FAIL		= 4,
}	t_token_res;

typedef enum e_link_type
{
	LINK_NONE,
	LINK_AND,
	LINK_OR,
}	t_link_type;

typedef struct s_syntax
{
	char	last_char;
	int		paren_depth;
}	t_syntax;

typedef struct s_pipe
{
	t_token_res		result;
	int				argc;
	char			**argv;
	int				redirect_in;
	int				redirect_out;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_token
{
	t_link_type		link_type;
	t_pipe			*pipes;
	t_pipe			*cur_pipe;
	int				stdin_origin;
	int				stdout_origin;
	int				p_open;
	int				p_close;
}	t_token;

typedef struct s_token_list
{
	int		interrupted;
	t_token	**tokens;
	int		size;
}	t_token_list;

typedef struct s_mem {
	void			*addr;
	int				collectible;
	struct s_mem	*next;
}	t_mem;

typedef struct s_sys
{
	char			**p_env;
	t_mem			*alloc_mem[HASH_MAX];
	struct termios	old_term;
	struct termios	new_term;
	int				reading_flag;
}	t_sys;

/* global variable */
t_sys			g_sys;

/* memory_manager.c */
void			*safe_malloc(size_t size);
void			*safe_malloc_uc(size_t size);
void			safe_free(void *addr);
void			garbage_collect(int force_flag);

/* signals.c */
void			init_handlers(void (*old_sigint)(int));

/* terms.c */
void			init_terms(void);
void			apply_new_term(void);
void			apply_old_term(void);

/* error_control.c */
void			print_error(t_error err, const char *s);
void			quit_shell(int code);

/* common_utils.c */
size_t			get_split_size(char **arr);
void			free_splited(char **arr, size_t size);
void			system_initialize(char **env);
int				hash(void *addr);

/* print_logo.c */
void			print_logo(void);

/* pipe.c */
void			do_commands(t_token *tokens);

/* pipe_restore.c */
void			redirect_save_origin(t_token *tokens);
int				redirect_in_restore(t_token *tokens);
int				redirect_out_restore(t_token *tokens);
void			pipe_wait(int *status, pid_t pid, int cmd_cnt);

/* pipe_utils.c */
int				get_cmd_count(t_pipe *pipes);
char			**get_cmd_paths(void);
char			*find_cmd_path(char **path, t_pipe *token);
char			**token_to_cmd_path(t_pipe *pipes, int cmd_count);
int				check_need_fork(t_token *tokens);

/* env_utils.c */
char			**copy_env(char **env, size_t size, size_t idx);
int				get_keylen(const char *key);
char			*get_env_val(const char *key);
int				change_env_value(char *key, char *ch_val);

/* builtin_*.c */
void			builtin_echo(t_pipe *token);
void			builtin_cd(t_pipe *token, int main_flag);
void			builtin_pwd(t_pipe *token);
void			builtin_exit(t_pipe *token, int main_flag);
void			builtin_export(t_pipe *token, int main_flag);
void			builtin_unset(t_pipe *token, int main_flag);
void			builtin_env(t_pipe *token, char *prompt);
int				is_builtin(const char *cmd);
void			exe_builtin(t_pipe *token);
char			*exchange_oldpwd_and_pwd(void);
void			check_cmd_in_builtin_env(t_token *tokens);

/* wildcard_utils.c */
char			**get_cwd_files(void);
int				wildcard_strcmp(char *wildcard, char *start, char *str);
char			*remove_backslash(char *str);

/* wildcard.c */
char			**find_wildcard_files(char *wildcard);

/* string_utils.c */
void			skip_space(const char **s);
void			skip_pipe(const char **s);
size_t			write_until_dollor(char *rd_buf, int fd, int flag);

/* syntax_checker.c */
char			*check_syntax(char *line);

/* syntax_supporter.c */
int				check_quote(t_syntax *syntax, char **line);
int				check_link(t_syntax *syntax, char **line);
int				check_redirect(t_syntax *syntax, char **line);
int				check_paren(t_syntax *syntax, char **line);
int				check_word(t_syntax *syntax, char *line);

/* tokenizer_counter.c */
int				token_word_len(const char *str, int dollar_flag);

/* tokenizer_heredoc*.c */
void			get_heredoc(t_token_list *list, const char **str, \
							void (*old_si)(int));
char			*heredoc_filename(void);
void			find_key_and_write(int fd, char *rd_buf, size_t len);
size_t			get_len_until_chr(char *str, char c);
size_t			get_delimitter_len(const char *str);
char			*copy_delimitter(const char **str, size_t len, int *conv_flag);

/* tokenizer_infile.c */
int				read_redirect(char *filename);
char			*parse_filename(t_token *token, const char **str);
void			get_infile(t_token *token, const char **str);

/* tokenizer_outfile.c */
int				write_redirect(char *filename, int append_flag);
void			get_outfile(t_token *token, const char **str, int append_flag);

/* tokenizer_links.c */
void			process_links(t_token_list *list, const char **str);
void			append_token(t_token_list *list);

/* tokenizer_parser.c */
char			*parse_word(const char **str, int dollar_flag);

/* tokenizer_utils.c */
void			init_token_list(t_token_list *list);
void			init_token(t_token *token);
char			*readline_with_nl(char *prompt);
void			create_pipe_info(t_token *token);
void			check_first_token(const char *line, t_token_list *list);

/* ft_readline.c */
char			*ft_readline(void);

/* parenthesis.c */
void			parse_parenthesis(t_token_list *list, const char **str);
int				token_parenthesis_recursive(t_token_list *list, int i);

/* tokenizer.c */
t_token_list	*tokenize(const char *line, void (*old_sigint)(int));

#endif
