/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:17:55 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 08:17:56 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	tick1(t_mlx *mlx)
{
	if (mlx->player->held_item == 1 && mlx->player->fuel > 0)
		draw_lantern(mlx);
	else if (mlx->player->held_item == 1)
		draw_unlit_lantern(mlx);
	else if (mlx->player->held_item == 2)
		draw_key(mlx);
	if (mlx->msg_counter > 0)
	{
		mlx->msg_counter--;
		redisplay_message(mlx);
	}
	else
	{
		mlx->msg_counter = -1;
		mlx_delete_image(mlx->mlx_p, mlx->msg);
		mlx->msg = NULL;
	}
	if (mlx->player->is_sprinting == 2
		&& (mlx->player->is_moving_forward != 0
			|| mlx->player->is_moving_sides != 0))
		mlx->player->endurance--;
	else
		mlx->player->endurance++;
}

void	tick2(t_mlx *mlx)
{
	if (mlx->player->endurance <= 0)
	{
		mlx->player->can_run = 0;
		mlx->player->is_sprinting = 0.5;
	}
	if (mlx->player->endurance >= MIN_END_TO_RUN
		&& mlx->player->can_run == 0)
	{
		mlx->player->can_run = 1;
		mlx->player->is_sprinting = 1;
	}
	if (mlx->player->endurance >= MAX_ENDURANCE)
		mlx->player->endurance = MAX_ENDURANCE;
	if (mlx->player->held_item == 1)
		mlx->player->fuel--;
	if (mlx->player->fuel <= 0)
	{
		mlx->player->fuel = 0;
		mlx->player->light_radius = DRAW_DISTANCE;
	}
}

void	victory_condition(t_mlx *mlx)
{
	if (mlx->data->victory == 1)
	{
		mlx->data->x++;
		if (mlx->data->x >= TIME_TO_END * 2)
			ft_exit(mlx);
		victory(mlx);
		victory_screen(mlx);
	}
	else
	{
		mlx->data->x++;
		if (mlx->data->x >= (TIME_TO_END * 2))
			ft_exit(mlx);
		defeat(mlx);
		defeat_screen(mlx);
	}
}

void	loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (!mlx->data->victory)
	{
		mlx_delete_image(mlx->mlx_p, mlx->img);
		mlx->img = mlx_new_image(mlx->mlx_p, WIDTH, HEIGHT);
		mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
		raycasting(mlx);
		//raycasting_door(mlx);
		redisplay_message(mlx);
		move(mlx, 0, 0);
		minimap_background(mlx);
		draw_minimap(mlx);
		grab_key(mlx);
		display_endurance(mlx);
		display_fuel(mlx);
		tick1(mlx);
		tick2(mlx);
		tick_sprites(mlx->controller);
	}
	else
		victory_condition(mlx);
}
