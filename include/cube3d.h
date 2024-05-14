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
# include "../MLX42/MLX42.h"
# include "libft.h"

# define WIDTH 1400
# define HEIGHT 800
# define TILE_SIZE 64
# define FOV 75
# define ROTATION_SPEED 0.4
# define PLAYER_SPEED 2
# define DRAW_DISTANCE 60
# define MINIMAP_SIZE 8
# define MINIMAP_MAX_X 12
# define MINIMAP_MAX_Y 8
# define TEXT_Y 700
# define TEXT_X 200

# define MAX_ENDURANCE 150
# define MIN_END_TO_RUN 90
# define ENDURANCE_POS_X 22
# define ENDURANCE_POS_Y 242
# define ENDURANCE_WIDTH 16
# define ENDURANCE_MAX_LEN 400
# define ENDURANCE_COLOR 0x34ebb4ff
# define ENDURANCE_SPENT 0x8a1c37ff

# define MINIMAP_COLOR_PLAYER 0x940007ff
# define MINIMAP_COLOR_WALL 0xc5885cff
# define MINIMAP_COLOR_DOOR 0x1c080fff
# define MINIMAP_COLOR_KEY 0xffe600ff
# define MINIMAP_COLOR_EXIT 0x05a81eff

# define MAX_FUEL 1500
# define FUEL_POS_X 68
# define FUEL_POS_Y 242
# define FUEL_WIDTH 16
# define FUEL_MAX_LEN 400
# define FUEL_COLOR 0xc9a616FF

# define NB_ELEMENTS 6

# define TIME_TO_END 125

# define LINE_INTRO "This place is cursed. I must find the MAGIC SCROLL \
to open the barriers and get away !"
# define LINE_LOCKED "I need the MAGIC SCROLL to destroy this barrier !"
# define LINE_KEY "I found the MAGIC SCROLL ! \
I can use it to break the barriers."
# define LINE_VICTORY "I did it !"

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
# define M_PI_ON_TWO 1.570796
# define M_THREE_PI_ON_TWO 4.71238898

typedef struct s_player
{
	int		player_x;
	int		player_y;
	int		evil_x;
	int		evil_y;
	int		left_right;
	int		up_down;
	int		is_rotating;
	int		is_moving_forward;
	int		is_moving_sides;
	int		has_key;
	int		light_radius;
	int		held_item;
	int		can_run;
	double	is_sprinting;
	double	angle;
	double	fuel;
	double	endurance;
	float	fov;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	double			planx;
	double			plany;
	double			dirx;
	double			diry;
	int		rayon;
	int		flag;
	int		horiz_x;
	int		horiz_y;
	int		vert_x;
	int		vert_y;
	char	wall_type;
	char	wall_type2;
}	t_ray;

# define IMAGES_IN_SPRITES 10
# define MAX_ANIMATIONS 10

typedef struct s_anim
{
	mlx_texture_t	*sprites[IMAGES_IN_SPRITES];
	mlx_texture_t	*current;
	int				index;
	int				delay;
}	t_anim;

typedef struct s_animation_controller
{
	t_anim	*sprite_set[MAX_ANIMATIONS];
	int		frame;
	int		frame_max;
}	t_contr;

typedef struct s_texset
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*c;
	mlx_texture_t	*f;
	mlx_texture_t	*barrel;
	mlx_texture_t	*evil;
	mlx_texture_t	*exit;
	mlx_texture_t	*map;
	mlx_texture_t	*lantern;
	mlx_texture_t	*lanternempty;
	mlx_texture_t	*handkey;
	mlx_texture_t	*victory;
	mlx_texture_t	*defeat;
	mlx_image_t		*mapi;
	mlx_image_t		*lanterni;
	mlx_image_t		*lanternemptyi;
	mlx_image_t		*handkeyi;
	mlx_image_t		*victoryi;
	mlx_image_t		*defeati;
	t_anim			*key;
	t_anim			*door;
}	t_texset;

typedef struct s_imgset
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*door_img;
	char	*floor_img;
	char	*ceiling_img;
	int		floor_color;
	int		ceiling_color;
}	t_imgset;

typedef struct s_data
{
	int			player_x;
	int			player_y;
	int			evil_x;
	int			evil_y;
	int			map_width;
	int			map_height;
	int			victory;
	int			perp_wall_dist;
	double		x;
	char		player_orientation;
	char		**map;
	t_imgset	*img;
	t_texset	*tex;
}	t_data;

typedef struct s_mlx
{
	mlx_image_t				*img;
	mlx_t					*mlx_p;
	t_ray					*ray;
	t_data					*data;
	t_player				*player;
	mlx_image_t				*msg;
	t_contr					*controller;
	int						msg_counter;
	float					x_step;
	float					y_step;
}	t_mlx;

/**
 * Core
*/
void	start(t_data *data);
void	loop(void *ml);
void	load_img(t_mlx *mlx);
void	load_img2(t_mlx *mlx);
void	init_player(t_mlx *mlx);
void	super_mega_init(t_mlx *mlx);
void	ft_exit(t_mlx *mlx);
void	defeat_screen(t_mlx *mlx);
void	victory_screen(t_mlx *mlx);

/**
 * Trucs de maths pas beau
*/
float	normalize_angle(float angle);

int		inter_check(float angle, float *inter, float *step, int is_border_wall);
int		unit_circle(float angle, char c);
int		get_rgba(int r, int g, int b, int a);
int		reverse_bytes(int c);
int		ppcm(int a, int b);

/**
 * Raycast et render
*/
double	get_x_wall(mlx_texture_t *texture, t_mlx *mlx);

float	get_v_inter(t_mlx *mlx, float angle);
float	get_h_inter(t_mlx *mlx, float angle);

int		wall_hit(float x, float y, t_mlx *mlx, int method);

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);

void	ft_exit(t_mlx *mlx);
void	loop(void *ml);
void	start(t_data *data);
void	raycasting(t_mlx *mlx);
void	raycasting_door(t_mlx *mlx);
void	mlx_put_pixel_screen(t_mlx *mlx, int x, int y, int color);
void	mlx_put_floor(t_mlx *mlx, int i, int ray, int c);
void	draw_square(t_mlx *mlx, int x, int y, int c);
void	draw_square2(t_mlx *mlx, int x, int y, int c);
void	draw_wall(t_mlx *mlx, int top_pixel, int bottom_pixel,
			double wall_height);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel,
			int bottom_pixel);
void	render_wall(t_mlx *mlx, int ray);
void	minimap_background(t_mlx *mlx);
void	draw_minimap(t_mlx *mlx);
void	draw_lantern(t_mlx *mlx);
void	draw_unlit_lantern(t_mlx *mlx);
void	draw_key(t_mlx *mlx);
void	display_message(t_mlx *mlx, char *msg);
void	redisplay_message(t_mlx *mlx);
void	display_fuel(t_mlx *mlx);
void	display_endurance(t_mlx *mlx);
void	victory(t_mlx *mlx);
void	defeat(t_mlx *mlx);

void	tick_sprite(t_anim *s);
void	tick_sprites(t_contr *a);

mlx_texture_t	*get_texture(t_mlx *mlx, int flag);

/**
 * Gestion des events
*/
void	press(mlx_key_data_t keydata, void *ml);
void	move_dude(t_mlx *mlx, double move_x, double move_y);
void	move(t_mlx *mlx, double move_x, double move_y);
void	open_doors(t_mlx *mlx);
void	open_exit(t_mlx *mlx);
void	grab_key(t_mlx *mlx);

/**
 * Gestion des animations
*/
void	load_sprites(t_mlx **mlx);
void	add_to_set(t_anim *s, char *tex);
void	tick_sprites(t_contr *a);
void	free_sprite(t_anim *s);
void	add_to_control(t_contr *a, t_anim *s);

t_anim	*create_sprite(int delay);

t_contr	*init_controller(void);

/**
 * Gestion du parser
*/

typedef struct s_chain
{
	char			*line;
	struct s_chain	*next;
	struct s_chain	*previous;
}	t_chain;

typedef struct s_tuple
{
	int	x;
	int	y;
}	t_tuple;

int		ft_equals(char *s1, char *s2);
int		is_whitespace(char c);
int		is_rgb(char *a);
int		is_line_map(char *l);
int		is_map_element(char c);
int		darken(int c, double dist, t_mlx *mlx);
int		colorpicker(int r, int g, int b);
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
void	get_position_evil(t_data *data);
void	remove_tail(t_chain *c);
void	cut_ligne(t_chain **c);
void	free_chain(t_chain *chain);
void	free_imgset(t_imgset *t);
void	free_data(t_data *d, t_chain *c);
void	free_split(char **a);
void	null_values(t_imgset **img);

char	**generate_map(t_chain *c, int x, int y);

void	render_sprite(t_mlx *mlx, int ray, char method);
void	raycasting_sprites(t_mlx *mlx);
void	do_sprite_stuff(t_mlx *mlx, float angle, int rayon);
int		sprite_hit(float x, float y, t_mlx *mlx);

t_data	*generate_data(char *path);
t_data	*data_error(int code, t_data *data, t_chain *values);
t_chain	*to_chain(char *path);

t_chain	*ft_errmsg(char *msg);

#endif
