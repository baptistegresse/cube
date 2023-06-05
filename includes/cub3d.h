/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:12:09 by jcluzet           #+#    #+#             */
/*   Updated: 2023/06/05 21:44:51 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
#include <string.h>

# if defined(__APPLE__) && defined(__MACH__)
#  define ADVANCE 13
#  define BACK 1
#  define RIGHT 2
#  define LEFT 0
#  define ROT_RIGHT 124
#  define ROT_LEFT 123
#  define ESC 53
#  define RED_BUTTON 79
#  define LIGHTS 29
#  define CLOSERED 17
# else
#  define ADVANCE 119
#  define BACK 115
#  define RIGHT 100
#  define LEFT 97
#  define ROT_RIGHT 65363
#  define ROT_LEFT 65361
#  define ESC 65307
#  define RED_BUTTON 79
#  define LIGHTS 48
#  define CLOSERED 33
# endif

# define WIN_W 1400
# define WIN_H 1000
# define ROT_SPEED 0.03f
# define SPEED 0.03f

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}				t_free;

typedef struct s_m_free
{
	struct s_free	*list;
}				t_m_free;

typedef struct s_float_vector
{
	float	x;
	float	y;
}	t_float_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_rgb
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
}	t_rgb;

typedef struct s_params
{
	char			*path_to_the_north_texture;
	char			*path_to_the_south_texture;
	char			*path_to_the_west_texture;
	char			*path_to_the_east_texture;
	t_rgb			celling_rgb;
	t_rgb			floor_rgb;
	int				celling_color;
	int				floor_color;
}	t_params;

typedef struct s_player
{
    t_float_vector pos;
    t_float_vector dir;
    t_float_vector move;
    t_float_vector plane;
    char dir_base;
    float rotation;
    float angle;
} t_player;

typedef struct	s_ray
{
	t_float_vector  pos;
	t_float_vector  dir;
	t_float_vector	side_dist;
	t_float_vector	delta_dist;
	t_float_vector	camera;
	t_int_vector	map;
	t_int_vector	step;
	float			perp_wall_dist;
	bool			hit;
	int				side;
}	t_ray;

typedef struct s_map
{
	int				no_path_set;
	int				we_path_set;
	int				so_path_set;
	int				ea_path_set;
	int				floor_color_set;
	int				ceiling_color_set;
	bool			before_params;
	int				start_line;
	int				num_of_player;
	char			**array;
	bool			**visited;
	int				width;
	int				height;
	int				wall_color;
}	t_map;

typedef struct s_win
{
    void			*mlx;
	void			*mlx_win;
    void			*img;
    char			*addr;
    int				bits_per_pixel;
	int				line_length;
	int				endian;
}   t_win;

typedef struct  s_keys
{
    bool    advance;
    bool    back;
    bool    right;
    bool    left;
    bool    rot_right;
    bool    rot_left;
}	t_keys;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	t_m_free		*garbage;
	t_map			map;
	t_player		player;
	t_params		params;
	t_win       	win;
    t_ray       	ray;
	t_keys			keys;
}	t_data;

t_m_free		*free_init(void);

void			ft_free(t_m_free *m_free);

void			*free_malloc(t_m_free *m_free, size_t size);

void			free_remove(t_m_free *m_free, void *ptr);
void			free_remove_if(t_free **begin_list, void *ptr_ref);

int				free_add(t_m_free *m_free, void *ptr);
int				free_add_value(t_m_free *m_free, t_free *new, t_free *tmp);

int				free_size(t_m_free *m_free);

/* check1_functions.c */

bool	textures_are_valid(t_data *data);
bool	is_map_line(char *line);
bool	check_value_of_map(t_data *data, char *line, int file_descriptor);
bool	check_validity_of_map(t_data *data, char *argv);

/* check2_functions.c */

bool	paths_rgb_are_filled(t_data *data);
bool	map_unclosed(t_data *data, int x, int y, bool **visited);
bool	cube_parser(t_data *data, char *argv);

/* init_functions.c */

int	init_data(t_data *data);

/* parse_map_functions.c */

bool	get_size_of_map(t_data *data, char *argv);
bool	malloc_map_visited(t_data *data);
void    get_position_player(t_data *data, float x, float y, char dir_base);
void	fill_map_array_line(t_data *data, char *line, int index);
bool	fill_map_array(t_data *data, char *argv);

/* parse_paths_rgb_functions.c */

void	get_color_value(t_data *data, t_rgb *rgb, char *line);
void	get_path_value(t_data *data, char **path, char *line);
void	fill_paths_rgb(t_data *data, char *line);
bool	paths_rgb_duplicate(t_data *data);
bool	get_file_paths_rgb(t_data *data, char *argv);

/* set_colors */

int     rgb_to_int(t_rgb color);
int     set_color_cell(t_data *data, int x, int y);

/* utils1_functions.c */

size_t	ft_strlen(const char *str);
char	*ft_strdup(t_data *data, const char *src);
int     ft_atoi(const char *str);

/* utils2_functions.c */

char	*get_next_line(t_data *data, int fd);
void	*ft_calloc(t_data *data, size_t num, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strndup(t_data *data, const char *src, size_t n);

/* handler.c */

int     handle_keypress(int keycode, t_data *data);

/* minimap.c */

void    drawRect(t_data *data, int x0, int y0, int width, int height, int color);
void    draw_minimap(t_data *data);
void    display_game(t_data *data);

/* mlx_utils.c */

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* raycasting.c */

void 	draw_3d(t_data *data);


void	put_pxl_img(t_img *img, int x, int y, int color);
void    raycasting(t_data *data);
int     handle_keyrelease(int keycode, t_data *data);
void    update_player(t_data *data);
#endif