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

void	mlx_put_pixel_screen(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	if (color == 0x00000000)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

void	draw_square2(t_mlx *mlx, int x, int y, int c)
{
	int	i;
	int	j;

	if (!c)
		return ;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			mlx_put_pixel_screen(mlx, j + x, i + y, c);
			j++;
		}
		i++;
	}
}

void	draw_square(t_mlx *mlx, int x, int y, int c)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			mlx_put_pixel_screen(mlx, j + x + 6
				* MINIMAP_SIZE + MINIMAP_SIZE / 2,
				i + y + 4 * MINIMAP_SIZE + MINIMAP_SIZE / 2, c);
			j++;
		}
		i++;
	}
}

int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0x00000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
	if (*(pixelstart + 3) == 0)
		return (0x00000000);
	return (get_rgba(*(pixelstart), *(pixelstart + 1),
			*(pixelstart + 2), *(pixelstart + 3)));
}

int	darken(int c, double dist, t_mlx *mlx)
{
	int	r;
	int	g;
	int	b;

	if (dist < mlx->player->light_radius)
		return (c);
	r = (c & 0xFF000000) >> 24;
	g = (c & 0x00FF0000) >> 16;
	b = (c & 0x0000FF00) >> 8;
	r -= ((dist - mlx->player->light_radius) / (mlx->player->light_radius)) * r;
	g -= ((dist - mlx->player->light_radius) / (mlx->player->light_radius)) * g;
	b -= ((dist - mlx->player->light_radius) / (mlx->player->light_radius)) * b;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (colorpicker(r, g, b));
}
