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

void	victory(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)((mlx->data->x / TIME_TO_END) * HEIGHT))
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel_screen(mlx, j, i, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	defeat(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)((mlx->data->x / TIME_TO_END) * HEIGHT))
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel_screen(mlx, j, HEIGHT / 2 - i, 0x000000FF);
			mlx_put_pixel_screen(mlx, j, HEIGHT / 2 + i, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	victory_screen(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)mlx->data->tex->victoryi->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->victoryi->width)
		{
			mlx_put_pixel_screen(mlx, j
				+ (WIDTH / 2 - mlx->data->tex->victoryi->width / 2),
				i + (HEIGHT / 2 - (int)mlx->data->tex->victoryi->height / 2),
				mlx_get_pixel(mlx->data->tex->victoryi, j, i));
			j++;
		}
		i++;
	}
}

void	defeat_screen(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)mlx->data->tex->defeati->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->defeati->width)
		{
			mlx_put_pixel_screen(mlx, j
				+ (WIDTH / 2 - mlx->data->tex->defeati->width / 2),
				i + (HEIGHT / 2 - (int)mlx->data->tex->defeati->height / 2),
				mlx_get_pixel(mlx->data->tex->defeati, j, i));
			j++;
		}
		i++;
	}
}
