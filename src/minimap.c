/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:33:08 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:33:09 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	minimap_draw_square(t_mlx *mlx, t_tuple *t, int x, int y)
{
	if (y == mlx->player->player_y / TILE_SIZE
		&& x == mlx->player->player_x / TILE_SIZE)
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, MINIMAP_COLOR_PLAYER);
	else if (mlx->data->map[y][x] == '1')
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, MINIMAP_COLOR_WALL);
	else if (mlx->data->map[y][x] == 'K')
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, MINIMAP_COLOR_KEY);
	else if (mlx->data->map[y][x] == 'D')
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, MINIMAP_COLOR_DOOR);
	else if (mlx->data->map[y][x] == 'X')
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, MINIMAP_COLOR_EXIT);
	else if (is_whitespace(mlx->data->map[y][x]))
	{
		t->x += 1;
		return ;
	}
	else
		draw_square(mlx, t->x * MINIMAP_SIZE, t->y * MINIMAP_SIZE, 0xe4ab68FF);
	t->x += 1;
}

int	condition1(t_mlx *mlx, int i)
{
	if (mlx->player->player_y / TILE_SIZE < MINIMAP_MAX_Y)
	{
		if (abs(i - mlx->player->player_y / TILE_SIZE)
			> MINIMAP_MAX_Y * 2 - mlx->player->player_y / TILE_SIZE)
			return (0);
	}
	else if (mlx->player->player_y / TILE_SIZE + MINIMAP_MAX_Y
		> mlx->data->map_height)
	{
		if (abs(i - mlx->player->player_y / TILE_SIZE)
			> MINIMAP_MAX_Y * 2 - abs(mlx->data->map_height
				- mlx->player->player_y / TILE_SIZE))
			return (0);
	}
	else if (abs(i - mlx->player->player_y / TILE_SIZE) > MINIMAP_MAX_Y)
		return (0);
	return (1);
}

int	condition2(t_mlx *mlx, int j)
{
	if (mlx->player->player_x / TILE_SIZE < MINIMAP_MAX_X)
	{
		if (abs(j - mlx->player->player_x / TILE_SIZE)
			> MINIMAP_MAX_X * 2 - mlx->player->player_x / TILE_SIZE)
			return (0);
	}
	else if (mlx->player->player_x / TILE_SIZE
		+ MINIMAP_MAX_X > mlx->data->map_width)
	{
		if (abs(j - mlx->player->player_x / TILE_SIZE)
			> MINIMAP_MAX_X * 2 - abs(mlx->data->map_width
				- mlx->player->player_x / TILE_SIZE))
			return (0);
	}
	else if (abs(j - mlx->player->player_x / TILE_SIZE) > MINIMAP_MAX_X)
		return (0);
	return (1);
}

void	draw_minimap(t_mlx *mlx)
{
	int		i;
	int		j;
	t_tuple	t;

	i = 0;
	t.y = 0;
	while (mlx->data->map[i])
	{
		j = 0;
		t.x = 0;
		if (!condition1(mlx, i))
		{
			i++;
			continue ;
		}
		while (mlx->data->map[i][j])
		{
			if (condition2(mlx, j))
				minimap_draw_square(mlx, &t, j, i);
			j++;
		}
		t.y++;
		i++;
	}
}
