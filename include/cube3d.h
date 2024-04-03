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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

#define WIDTH 1900
#define HEIGHT 1000
#define TILE_SIZE 30
#define FOV 60
#define ROTATION_SPEED 0.045
#define PLAYER_SPEED 4
#define WE 0xB5B5B5FF
#define NS 0xF5F5F5FF

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
        double ray_angle;
        double distance;
        int flag;
        int horiz_x;
        int vert_y;
} t_ray;

typedef struct s_data
{
        char **map;
        int player_x;
        int player_y;
        char player_orientation;
        int map_width;
        int map_height;
        //t_imgset *img;
} t_data;

typedef struct s_mlx
{
        mlx_image_t     *img;
        mlx_t           *mlx_p;
        t_ray   *ray;
        t_data  *data;
        t_player       *player;
} t_mlx;

void	ft_exit(t_mlx *mlx);
void	loop(void *ml);
void	init_player(t_mlx mlx);
void	start(t_data *data);
t_data	*init_map();
int	main();
void	raycasting(t_mlx *mlx);
float   get_v_inter(t_mlx *mlx, float angle);
float   get_h_inter(t_mlx *mlx, float angle);
int	wall_hit(float x, float y, t_mlx *mlx);
int     inter_check(float angle, float *inter, float *step, int is_border_wall);
int     unit_circle(float angle, char c);
float	normalize_angle(float angle);
void	mlx_pixel_put_screen(t_mlx, int x, int y, int color);
int	get_rgba(int r, int g, int b, int a);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel);
mlx_texture_t	*get_texture(t_mlx *mlx, int flag);
double get_x_wall(mlx_texture_t	*texture, tmlx *mlx);
int	reverse_bytes(int c);
void	draw_wall(t_mlx *mlx, int top_pixel, int bottom_pixel, double wall_height);
void	render_wall(t_mlx *mlx, int ray);

