/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:19:08 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:19:09 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	init_player(t_mlx *mlx)
{
	mlx->player->player_x = mlx->data->player_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->player_y = mlx->data->player_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->fov = (FOV * M_PI) / 180;
	if (mlx->data->player_orientation == 'S')
		mlx->player->angle = M_PI / 2;
	else if (mlx->data->player_orientation == 'N')
		mlx->player->angle = (3 * M_PI) / 2;
	else if (mlx->data->player_orientation == 'W')
		mlx->player->angle = M_PI;
	else
		mlx->player->angle = 0;
}

void	init_2(t_mlx *mlx)
{
	mlx->player->is_rotating = 0;
	mlx->player->is_moving_sides = 0;
	mlx->player->is_moving_forward = 0;
	mlx->player->left_right = 0;
	mlx->player->up_down = 0;
	mlx->ray->rayon = 0;
	mlx->ray->ray_angle = 0;
	mlx->ray->distance = 0;
	mlx->ray->flag = 0;
	mlx->ray->wall_type = 0;
	mlx->ray->horiz_x = 0;
	mlx->ray->vert_y = 0;
	mlx->msg_counter = 250;
	mlx->data->victory = 0;
	mlx->player->evil_x = mlx->data->evil_x * TILE_SIZE + TILE_SIZE / 2;
	mlx->player->evil_y = mlx->data->evil_y * TILE_SIZE + TILE_SIZE / 2;
	mlx->controller = init_controller();
}

void	super_mega_init(t_mlx *mlx)
{
	mlx->player->player_x = mlx->data->player_x;
	mlx->player->player_y = mlx->data->player_y;
	mlx->player->light_radius = DRAW_DISTANCE;
	mlx->player->held_item = 0;
	mlx->player->is_sprinting = 1;
	mlx->player->has_key = 0;
	mlx->player->endurance = MAX_ENDURANCE;
	mlx->player->can_run = 1;
	mlx->player->fuel = MAX_FUEL;
	mlx->player->fov = FOV;
	init_2(mlx);
	init_player(mlx);
}
