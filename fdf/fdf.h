/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:11:13 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/06 18:40:32 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define _USE_MATH_DEFINES
# define BUFFER_SIZE 256
# define MAX_WIDTH 2400
# define MAX_HEIGHT 1200
# define AREA_MARGIN 60
# define PIXEL_GAP 47

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_O 31
# define KEY_U 32
# define KEY_I 34
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_0 29
# define KEY_PLUS 24
# define KEY_MINUS 27

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_map
{
	int	width;
	int	height;
	int	gap_pixel;
	int	**color;
	int	**data;
}	t_map;

typedef struct s_cod_2d
{
	int	x;
	int	y;
	int	color;
}	t_cod_2d;

typedef struct s_cod_3d
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_cod_3d;

typedef struct s_line_3d
{
	t_cod_3d	from;
	t_cod_3d	to;
}	t_line_3d;

typedef struct s_hook_var
{
	t_map		*map;
	t_cod_3d	**cod;
	t_vars		*var;
	t_cod_2d	*origin;
	int			yaw_angle;
	int			pitch_angle;
	int			roll_angle;
	t_img		*black_screen;
	t_img		*para_front;
	t_img		*para_side;
	t_img		*para_top;
}	t_hook_var;

typedef enum e_error_no
{
	NO_ERR,
	ERR_WRONG_INPUT,
	ERR_NO_FILE,
	ERR_NO_DATA,
	ERR_WRONG_LENGTH,
	ERR_ALLOC_FAIL,
}	t_error_no;

typedef enum e_parallel
{
	PARA_FRONT,
	PARA_SIDE,
	PARA_TOP,
}	t_parallel;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
size_t		count_words(char const *s, char c);
char		**ft_split(char const *s, char c);
int			hex_to_int(char *s);

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
ssize_t		ft_strnchr(const char *s, char c, size_t len);
size_t		ft_strlcpy(char *s1, const char *s2, size_t n);
t_list		*make_strlst(void);
void		*free_lst(t_list *lst, char **s);

t_cod_3d	**make_coordinate(t_map *map);
void		map_to_coordinate(t_map *map, t_cod_3d **cod);
t_cod_2d	calculate_2d_pos(t_cod_3d cod, int gap);

void		yaw_rotate(t_hook_var *var, double angle);
void		pitch_rotate(t_hook_var *var, double angle);
void		roll_rotate(t_hook_var *var, double angle);

t_vars		*init_and_set_window(t_map *map);
t_img		*make_image(t_vars *var);
void		draw_map(t_map *map, t_vars *var, t_cod_3d **cod, t_cod_2d *ori);

void		set_images(t_hook_var *vars);
void		img_draw_2d_line(char *addr, t_cod_2d from, t_cod_2d to);
int			get_max_height(t_hook_var *vars);
int			gap_resize(t_hook_var *vars, int w, int h);
t_cod_2d	set_2d_value1(int x1, int x2, int y, int color);
t_cod_2d	set_2d_value2(t_map *map, int i, int j, int gap);

int			hook_control(int keycode, t_hook_var *vars);

void		ft_swap(int *a, int *b);
int			absolute(int a);
int			get_max(int a, int b);

void		print_error(t_error_no errno, char *s_err);

t_map		*file_parsing(char *file_name);

#endif
