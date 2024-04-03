/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:47:28 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/28 13:00:45 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "parser.h"
# include "libft.h"

#define WIDTH 1900
#define HEIGHT 1000
#define TILE_SIZE 30
#define FOV 60
#define ROTATION_SPEED 0.2
#define PLAYER_SPEED 4
#define WE 0xB5B5B5FF
#define NS 0xF5F5F5FF

# define NB_ELEMENTS 6

# define ERR_NOT_ENOUGH_HEADERS 1
# define ERR_TOO_MUCH_HEADERS 2
# define ERR_EMPTY_LINE_IN_MAP 3
# define ERR_HEADER_IN_MAP 4
# define ERR_UNKNOWN_HEADER 5
# define ERR_HEADER_TOO_LARGE 6
# define ERR_HEADER_TOO_THIN 7
# define ERR_INVALID_RGB 8
# define ERR_UNKNOWN_CHARS 9
# define ERR_INVALID_ENTRIES 10
# define ERR_UNCLOSED_MAP 11
# define ERR_NON_UNIQUE_HEADER 12
# define ERR_FILE_NOT_FOUND 404

# define M_PI 3.14159265358979323846

typedef struct s_player
{
        int player_x;
        int player_y;
        double angle;
        float fov;
        int rotation;
        int left_right;
        int up_down;
} t_player;

typedef struct s_ray
{
	int	rayon;
        double ray_angle;
        double distance;
        int flag;
        int horiz_x;
        int vert_y;
} t_ray;

typedef struct s_texset
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_texset;

typedef struct s_imgset
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_img;
	char	*ceiling_img;
	int		floor_color;
	int		ceiling_color;
}	t_imgset;

typedef struct s_data
{
	int			player_x;
	int			player_y;
	int			map_width;
	int			map_height;
	char		player_orientation;
	char		**map;
	t_imgset	*img;
	t_texset	*tex;
}	t_data;


typedef struct s_mlx
{
        mlx_image_t     *img;
        mlx_t           *mlx_p;
        t_ray   *ray;
        t_data  *data;
        t_player       *player;
} t_mlx;

typedef struct s_chain
{
	char			*line;
	struct s_chain	*next;
	struct s_chain	*previous;
}	t_chain;


void	ft_exit(t_mlx *mlx);
void	loop(void *ml);
void	init_player(t_mlx mlx);
void	start(t_data *data);
int	main();
void	raycasting(t_mlx *mlx);
float   get_v_inter(t_mlx *mlx, float angle);
float   get_h_inter(t_mlx *mlx, float angle);
int	wall_hit(float x, float y, t_mlx *mlx);
int     inter_check(float angle, float *inter, float *step, int is_border_wall);
int     unit_circle(float angle, char c);
float	normalize_angle(float angle);
void	mlx_put_pixel_screen(t_mlx *mlx, int x, int y, int color);
int	get_rgba(int r, int g, int b, int a);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel);
mlx_texture_t	*get_texture(t_mlx *mlx, int flag);
double get_x_wall(mlx_texture_t	*texture, t_mlx *mlx);
int	reverse_bytes(int c);
void	draw_wall(t_mlx *mlx, int top_pixel, int bottom_pixel, double wall_height);
void	render_wall(t_mlx *mlx, int ray);

int		ft_equals(char *s1, char *s2);
int		is_whitespace(char c);
int		is_rgb(char *a);
int		is_line_map(char *l);
int		is_map_element(char c);
int		get_rgb(char *a);
int		emptyline(char *c);
int		check_map(t_data *d);
int		map_length(t_chain *c);
int		map_lines(t_chain *c);
int		split_len(char **a);
int		check_exists(t_imgset *img);
int		epure(t_chain *c);
int		generate_imgset(t_chain *c, t_imgset *img);
int		has_null_values(t_imgset *img);
int		part_one_img(t_imgset **img, char **li);
int		part_two_img(t_imgset **img, char **li);
int		part_three_img(t_imgset **img, char **li);
int		part_four_img(t_imgset **img, char **li);

void	get_positions(t_data *data);
void	remove_tail(t_chain *c);
void	cut_ligne(t_chain **c);
void	free_chain(t_chain *chain);
void	free_imgset(t_imgset *t);
void	free_data(t_data *d, t_chain *c);
void	free_split(char **a);
void	null_values(t_imgset **img);

char	**generate_map(t_chain *c, int x, int y);

t_data	*generate_data(char *path);
t_data	*data_error(int code, t_data *data, t_chain *values);
t_chain	*to_chain(char *path);

t_chain	*ft_errmsg(char *msg);

#endif
