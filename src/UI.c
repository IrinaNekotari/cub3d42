/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:25:44 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:25:45 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	minimap_background(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)mlx->data->tex->map->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->map->width)
		{
			draw_square2(mlx, j * 2, i * 2,
				mlx_get_pixel(mlx->data->tex->mapi, j, i));
			j++;
		}
		i++;
	}
}

void	draw_key(t_mlx *mlx)
{
	int	i;
	int	j;

	i = HEIGHT / 2 - mlx->data->tex->handkeyi->height / 2;
	i = 0;
	while (i < (int)mlx->data->tex->handkeyi->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->handkeyi->width)
		{
			draw_square2(mlx, j * 2 + WIDTH - mlx->data->tex->handkeyi->width
				* 2, i * 2 + HEIGHT / 2 - mlx->data->tex->handkeyi->height
				/ 2, mlx_get_pixel(mlx->data->tex->handkeyi, j, i));
			j++;
		}
		i++;
	}
}

void	draw_unlit_lantern(t_mlx *mlx)
{
	int	i;
	int	j;

	i = HEIGHT / 2 - mlx->data->tex->lanternemptyi->height / 2;
	i = 0;
	while (i < (int)mlx->data->tex->lanternemptyi->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->lanternemptyi->width)
		{
			draw_square2(mlx, j * 2 + WIDTH
				- mlx->data->tex->lanternemptyi->width
				* 2, i * 2 + HEIGHT / 2 - mlx->data->tex->lanternemptyi->height
				/ 2, mlx_get_pixel(mlx->data->tex->lanternemptyi, j, i));
			j++;
		}
		i++;
	}
}

void	draw_lantern(t_mlx *mlx)
{
	int	i;
	int	j;

	i = HEIGHT / 2 - mlx->data->tex->lanterni->height / 2;
	i = 0;
	while (i < (int)mlx->data->tex->lanterni->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->lanterni->width)
		{
			draw_square2(mlx, j * 2 + WIDTH - mlx->data->tex->lanterni->width
				* 2, i * 2 + HEIGHT / 2 - mlx->data->tex->lanterni->height
				/ 2, mlx_get_pixel(mlx->data->tex->lanterni, j, i));
			j++;
		}
		i++;
	}
}
