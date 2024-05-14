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

void	do_sprite_stuff3(t_mlx *mlx, float *x, float *y, int rayon)
{
	while ((*x / TILE_SIZE) != mlx->player->player_x / TILE_SIZE
		&& (*y / TILE_SIZE) != mlx->player->player_y / TILE_SIZE)
	{
		if (*x < 0 || *y < 0)
			break ;
		get_sprite_id(mlx, *x, *y, rayon);
		*x -= mlx->x_step;
		*y -= mlx->y_step;
	}
}

void	do_sprite_stuff2(t_mlx *mlx, float angle, int rayon)
{
	float	h_x;
	float	h_y;
	int		pixel;

	mlx->y_step = TILE_SIZE;
	mlx->x_step = TILE_SIZE / tan(angle);
	h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &mlx->y_step, 1);
	h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angle);
	mlx->ray->flag = 0;
	if ((unit_circle(angle, 'y') && mlx->x_step > 0)
		|| (!unit_circle(angle, 'y') && mlx->x_step < 0))
		mlx->x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx, 1))
	{
		h_x += mlx->x_step;
		h_y += mlx->y_step;
	}
	do_sprite_stuff3(mlx, &h_x, &h_y, rayon);
}

void	do_sprite_stuff(t_mlx *mlx, float angle, int rayon)
{
	float	v_x;
	float	v_y;
	int		pixel;

	mlx->x_step = TILE_SIZE;
	mlx->y_step = TILE_SIZE * tan(angle);
	v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &mlx->x_step, 0);
	mlx->ray->flag = 1;
	v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && mlx->y_step < 0)
		|| (!unit_circle(angle, 'x') && mlx->y_step > 0))
		mlx->y_step *= -1;
	while (sprite_hit(v_x - pixel, v_y, mlx))
	{
		v_x += mlx->x_step;
		v_y += mlx->y_step;
	}
	do_sprite_stuff3(mlx, &v_x, &v_y, rayon);
}
