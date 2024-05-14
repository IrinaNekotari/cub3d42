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

void	get_sprite_id(t_mlx *mlx, float x, float y, int rayon)
{
	mlx->ray->horiz_x = x;
	mlx->ray->horiz_y = y;
	mlx->ray->vert_x = x;
	mlx->ray->vert_y = y;
	if (mlx->data->map[(int)floor(y / TILE_SIZE)]
		[(int)floor(x / TILE_SIZE)] == 'B'
		|| mlx->data->map[(int)floor(y / TILE_SIZE)]
		[(int)floor(x / TILE_SIZE)] == 'K')
	{
		mlx->ray->distance = sqrt(pow(((int)(x / TILE_SIZE) + 0.5) * TILE_SIZE
					- mlx->player->player_x, 2)
				+ pow(((int)(y / TILE_SIZE) + 0.5)
					* TILE_SIZE - mlx->player->player_y, 2));
		render_sprite(mlx, rayon, mlx->data->map
		[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)]);
	}
	if ((int)floor(y / TILE_SIZE) == (int)floor(mlx->player->evil_y / TILE_SIZE)
		&& (int)floor(x / TILE_SIZE) == (int)floor(
			mlx->player->evil_x / TILE_SIZE))
	{
		mlx->ray->distance = sqrt(pow(mlx->player->evil_x
					- mlx->player->player_x, 2)
				+ pow(mlx->player->evil_y - mlx->player->player_y, 2));
		render_sprite(mlx, rayon, 'V');
	}
}

void	raycasting_sprites(t_mlx *mlx)
{
	int	rayon;

	rayon = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
	while (rayon < WIDTH)
	{
		if (get_h_inter(mlx, normalize_angle(mlx->ray->ray_angle))
			>= get_v_inter(mlx, normalize_angle(mlx->ray->ray_angle)))
			do_sprite_stuff(mlx, normalize_angle(mlx->ray->ray_angle), rayon);
		else
			do_sprite_stuff2(mlx, normalize_angle(mlx->ray->ray_angle), rayon);
		rayon++;
		mlx->ray->ray_angle += (mlx->player->fov / WIDTH);
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
