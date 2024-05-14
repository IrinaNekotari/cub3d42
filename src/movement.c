/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:05:49 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/20 14:20:47 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	rotato(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED / 10;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED / 10;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void	move_dude(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_grid_x = ((new_x + move_x * 5) / TILE_SIZE);
	map_grid_y = ((new_y + move_y * 5) / TILE_SIZE);
	if (mlx->data->map[map_grid_y][map_grid_x] != '1'
		&& mlx->data->map[map_grid_y][map_grid_x] != 'D'
		&& mlx->data->map[map_grid_y][map_grid_x] != 'X'
		&& (mlx->data->map[map_grid_y][mlx->player->player_x / TILE_SIZE] != '1'
		&& mlx->data->map
			[mlx->player->player_y / TILE_SIZE][map_grid_x] != '1'))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
	grab_key(mlx);
}

static void	move2(t_mlx *mlx, double *move_x, double *move_y)
{
	if (mlx->player->is_moving_forward == -1)
	{
		*move_x += cos(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
		*move_y += sin(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
	}
	if (mlx->player->is_moving_forward == 1)
	{
		*move_x += -cos(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
		*move_y += -sin(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
	}
}

void	move(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->is_rotating == 1)
		rotato(mlx, 1);
	if (mlx->player->is_rotating == -1)
		rotato(mlx, 0);
	if (mlx->player->is_moving_sides == -1)
	{
		move_x += -sin(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
		move_y += cos(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
	}
	if (mlx->player->is_moving_sides == 1)
	{
		move_x += sin(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
		move_y += -cos(mlx->player->angle) * PLAYER_SPEED
			* mlx->player->is_sprinting;
	}
	move2(mlx, &move_x, &move_y);
	move_dude(mlx, move_x, move_y);
}
