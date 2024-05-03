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

void	raycasting_sprites(t_mlx *mlx)
{
	int	rayon;

	rayon = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
	while (rayon < WIDTH)
	{
		mlx->ray->flag = 0;
		mlx->ray->wall_type = 0;
		mlx->ray->wall_type2 = 0;
		do_sprite_stuff(mlx, normalize_angle(mlx->ray->ray_angle), rayon);
		rayon++;
		mlx->ray->ray_angle += (mlx->player->fov / WIDTH);
	}
}

float	do_sprite_stuff(t_mlx *mlx, float angle, int rayon)
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
	while (sprite_hit(v_x - pixel, v_y, mlx, 0))
	{
		v_x += x_step;
		v_y += y_step;
	}
	while ((v_x / TILE_SIZE) != mlx->player->player_x / TILE_SIZE && (v_y / TILE_SIZE) != mlx->player->player_y / TILE_SIZE)
    	{
    		if (mlx->ray->wall_type == 'B')
    		{
    			mlx->ray->distance = sqrt(pow(v_x - mlx->player->player_x, 2) + pow(v_y - mlx->player->player_y, 2));
			render_sprite(mlx, rayon);
		}
		v_x -= x_step;
       	v_y -= y_step;
      	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->player->player_x, 2)
			+ pow(v_y - mlx->player->player_y, 2)));
}

/*float	get_h_inter_sprites(t_mlx *mlx, float angle)
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
	while (sprite_hit(h_x, h_y - pixel, mlx, 1))
	{
		h_x += x_step;
		h_y += y_step;
	}
	while ((h_x / TILE_SIZE) != mlx->player->player_x && (h_y / TILE_SIZE) != mlx->player->player_y)
    	{
    		if (mlx->ray->wall_type == 'B')
			render_sprite(mlx, rayon);
		h_x -= x_step;
       	h_y -= y_step;
      	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - mlx->player->player_x, 2)
			+ pow(h_y - mlx->player->player_y, 2)));
}*/

int	sprite_hit(float x, float y, t_mlx *mlx, int method)
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
		{
			if (!method)
				mlx->ray->wall_type = mlx->data->map[y_m][x_m];
			else
				mlx->ray->wall_type2 = mlx->data->map[y_m][x_m];
			return (0);
		}
	}
	return (1);
}
