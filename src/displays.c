/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:22:50 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:22:51 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	redisplay_message(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	if (!mlx->msg)
		return ;
	while (i < mlx->msg->instances[0].y + (int)mlx->msg->height)
	{
		j = 0;
		while (j < mlx->msg->instances[0].x + (int)mlx->msg->width)
		{
			mlx_put_pixel_screen(mlx, j + TEXT_X, i + TEXT_Y, mlx_get_pixel(mlx->msg, j, i));
			j++;
		}
		i++;
	}
}

void	display_message(t_mlx *mlx, char *msg)
{
	if (mlx->msg)
		mlx_delete_image(mlx->mlx_p, mlx->msg);
	mlx->msg_counter = 250;
	mlx->msg = mlx_put_string(mlx->mlx_p, msg, TEXT_X, TEXT_Y);
}

void	display_fuel(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)((mlx->player->fuel / MAX_FUEL) * FUEL_MAX_LEN))
	{
		j = 0;
		while (j < FUEL_WIDTH)
		{
			mlx_put_pixel_screen(mlx, j + FUEL_POS_X,
				i + FUEL_POS_Y, FUEL_COLOR);
			j++;
		}
		i++;
	}
}

void	display_endurance(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)((mlx->player->endurance / MAX_ENDURANCE)
		* ENDURANCE_MAX_LEN))
	{
		j = 0;
		while (j < ENDURANCE_WIDTH)
		{
			if (mlx->player->can_run)
				mlx_put_pixel_screen(mlx, j + ENDURANCE_POS_X,
					i + ENDURANCE_POS_Y, ENDURANCE_COLOR);
			else
				mlx_put_pixel_screen(mlx, j + ENDURANCE_POS_X,
					i + ENDURANCE_POS_Y, ENDURANCE_SPENT);
			j++;
		}
		i++;
	}
}
