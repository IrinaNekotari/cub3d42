/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:10:26 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:10:27 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	grab_key(t_mlx *mlx)
{
	if (mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE] == 'K')
	{
		display_message(mlx,
			"I found the MAGIC SCROLL ! I can use it to break the barriers.");
		mlx->player->has_key = 1;
		mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE] = '0';
	}
}

int	is_looking_at_door(double angle, double dir)
{
	double	min;
	double	max;

	min = dir - M_PI / 4;
	max = dir + M_PI / 4;
	angle -= M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle >= min && dir <= max)
		return (1);
	return (0);
}

static void	open_2(t_mlx *mlx, double dir)
{
	if (mlx->player->held_item == 2 && dir == 0)
		mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE + 1] = '0';
	else if (mlx->player->held_item == 2 && dir == M_PI)
		mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE - 1] = '0';
	else if (mlx->player->held_item == 2 && dir == M_THREE_PI_ON_TWO)
		mlx->data->map[mlx->player->player_y / TILE_SIZE + 1]
		[mlx->player->player_x / TILE_SIZE] = '0';
	else if (mlx->player->held_item == 2 && dir == M_PI_ON_TWO)
		mlx->data->map[mlx->player->player_y / TILE_SIZE - 1]
		[mlx->player->player_x / TILE_SIZE] = '0';
	else
		display_message(mlx,
			"I need the MAGIC SCROLL to destroy this barrier !");
}

void	open_doors(t_mlx *mlx)
{
	double	dir;

	if (mlx->data->map[mlx->player->player_y / TILE_SIZE - 1]
		[mlx->player->player_x / TILE_SIZE] == 'D')
		dir = M_PI_ON_TWO;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE + 1]
		[mlx->player->player_x / TILE_SIZE] == 'D')
		dir = M_THREE_PI_ON_TWO;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE - 1] == 'D')
		dir = M_PI;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE]
		[mlx->player->player_x / TILE_SIZE + 1] == 'D')
		dir = 0;
	else
		return ;
	if (is_looking_at_door(mlx->player->angle, dir))
		open_2(mlx, dir);
}
