/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:05:02 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 08:05:07 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	release3(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		if (mlx->player->held_item == 2)
			mlx->player->held_item = 0;
		else if (mlx->player->has_key)
		{
			mlx->player->held_item = 2;
			mlx->player->light_radius = DRAW_DISTANCE;
		}
	}
}

static void	release2(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		if (mlx->player->held_item == 1)
		{
			mlx->player->held_item = 0;
			mlx->player->light_radius = DRAW_DISTANCE;
		}
		else
		{
			mlx->player->held_item = 1;
			if (mlx->player->fuel > 0)
				mlx->player->light_radius = DRAW_DISTANCE * 2;
			else
				mlx->player->light_radius = DRAW_DISTANCE;
		}
	}
}

void	release(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->player->is_rotating = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->player->is_rotating = 0;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_forward = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_forward = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_sides = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_sides = 0;
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
	{
		if (mlx->player->can_run)
			mlx->player->is_sprinting = 1;
		else
			mlx->player->is_sprinting = 0.5;
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		open_doors(mlx);
	release2(keydata, mlx);
	release3(keydata, mlx);
}

void	press(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_exit(mlx);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->player->is_rotating = -1;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->player->is_rotating = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->player->is_moving_forward = -1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		mlx->player->is_moving_forward = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		mlx->player->is_moving_sides = 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		mlx->player->is_moving_sides = -1;
	if (keydata.key == MLX_KEY_LEFT_SHIFT
		&& keydata.action == MLX_PRESS && mlx->player->can_run)
		mlx->player->is_sprinting = 2;
	release(keydata, mlx);
}
