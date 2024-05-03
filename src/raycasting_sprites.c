/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:28:51 by mjuette           #+#    #+#             */
/*   Updated: 2024/05/03 14:28:56 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	do_sprite_stuff2(t_mlx *mlx, float angle, int rayon)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0)
		|| (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx, 1))
	{
		h_x += x_step;
		h_y += y_step;
	}
	while ((h_x / TILE_SIZE) != mlx->player->player_x / TILE_SIZE && (h_y / TILE_SIZE) != mlx->player->player_y / TILE_SIZE)
    {
    	if (h_x < 0 || h_y < 0)
			break ;
		if (mlx->data->map[(int)floor(h_y / TILE_SIZE)][(int)floor(h_x / TILE_SIZE)] == 'B')
    	{
    		mlx->ray->horiz_x = h_x;
			mlx->ray->horiz_y = h_y;
			mlx->ray->distance = sqrt(pow(((int)(h_x / TILE_SIZE) + 0.5) * TILE_SIZE - mlx->player->player_x, 2) + pow(((int)(h_y / TILE_SIZE) + 0.5) * TILE_SIZE - mlx->player->player_y, 2));
			render_sprite(mlx, rayon);
		}
		h_x -= x_step;
       	h_y -= y_step;
    }
}

void	raycasting_sprites(t_mlx *mlx)
{
	int	rayon;

	rayon = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
	while (rayon < WIDTH)
	{
		if (get_h_inter(mlx, normalize_angle(mlx->ray->ray_angle)) > get_v_inter(mlx, normalize_angle(mlx->ray->ray_angle)))
			do_sprite_stuff(mlx, normalize_angle(mlx->ray->ray_angle), rayon);
		else
			do_sprite_stuff2(mlx, normalize_angle(mlx->ray->ray_angle), rayon);
		rayon++;
		mlx->ray->ray_angle += (mlx->player->fov / WIDTH);
	}
}

void	do_sprite_stuff(t_mlx *mlx, float angle, int rayon)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0)
		|| (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (sprite_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	while ((v_x / TILE_SIZE) != mlx->player->player_x / TILE_SIZE && (v_y / TILE_SIZE) != mlx->player->player_y / TILE_SIZE)
    {
    	if (v_x < 0 || v_y < 0)
			break ;
		if (mlx->data->map[(int)floor(v_y / TILE_SIZE)][(int)floor(v_x / TILE_SIZE)] == 'B')
    	{
			mlx->ray->horiz_x = v_x;
			mlx->ray->horiz_y = v_y;
    		mlx->ray->distance = sqrt(pow(((int)(v_x / TILE_SIZE) + 0.5) * TILE_SIZE - mlx->player->player_x, 2) + pow(((int)(v_y / TILE_SIZE) + 0.5) * TILE_SIZE - mlx->player->player_y, 2));
			render_sprite(mlx, rayon);
		}
		v_x -= x_step;
       	v_y -= y_step;
    }
}

int	sprite_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= mlx->data->map_height || x_m >= mlx->data->map_width))
		return (0);
	if (mlx->data->map[y_m] && x_m <= (int)strlen(mlx->data->map[y_m]))
	{
		if (mlx->data->map[y_m][x_m] == '1')
			return (0);
		if (mlx->data->map[y_m][x_m] == 'D' || mlx->data->map[y_m][x_m] == 'X')
			return (0);
	}
	return (1);
}
