/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:25:47 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 09:39:40 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include "gnl.h"

# define EPIPE 32
# define ECHILD 10
# define EAGAIN 11

typedef struct s_arg
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	int		cmd_count;
	char	***cmds;
	char	**paths;
}	t_arg;

typedef enum e_error
{
	ERR_NONE,
	ERR_OPEN_FAIL,
	ERR_PERM_DENY,
	ERR_PARAM,
	ERR_NO_CMD,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP,
	ERR_CHILD_FAIL,
	ERR_CLOSE,
	ERR_MALLOC,
}	t_error;

t_arg	*file_parse(int ac, char **av, char **env);
int		pipe_line(t_arg *args, char **env);
int		here_doc(t_arg *args, char **env);

void	whole_read_write(int read_fd, int write_fd);

void	file_to_pipe(t_arg *args);
void	str_to_pipe(char *buffer);
void	pipe_mulit_process(t_arg *args, int cnt, char **env);
int		pipe_to_file(t_arg *args, int cnt, char **env);

void	path_dir_check(char *filename);
char	**here_doc_strs(char *s);

char	**quatation_string_parse(char *str);
void	print_error(t_error err, char *s);

#endif
