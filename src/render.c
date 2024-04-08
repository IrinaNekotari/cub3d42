/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:33 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/28 14:47:53 by mjuette          ###   ########.fr       */
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
	mlx_put_pixel(mlx->img, x , y, color);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	i;
	int	c;

	i = bottom_pixel;
	c = mlx->data->img->ceiling_color;
	ft_printf("Color : %x\n", c);
	while (i < HEIGHT)
		mlx_put_pixel_screen(mlx, ray, i++, c);
	c = mlx->data->img->floor_color;
	i = 0;
	while (i < top_pixel)
		mlx_put_pixel_screen(mlx, ray, i++, c);
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = normalize_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->data->tex->ea);
		else
			return (mlx->data->tex->we);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->data->tex->so);
		else
			return (mlx->data->tex->no);
	}
}

double get_x_wall(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_wall;
	
	if (mlx->ray->flag == 1)
		x_wall = (int)fmodf((mlx->ray->horiz_x * (texture->width / TILE_SIZE)), texture->width);
	else
		x_wall = (int)fmodf((mlx->ray->vert_y * (texture->width / TILE_SIZE)), texture->width);
	return (x_wall);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_mlx *mlx, int top_pixel, int bottom_pixel, double wall_height)
{
	double	x_wall;
	double	y_wall;
	uint32_t	*color;
	mlx_texture_t	*texture;

	texture = get_texture(mlx, mlx->ray->flag);
	color = (uint32_t *)texture->pixels;
	x_wall = get_x_wall(texture, mlx);
	y_wall = (texture->height / wall_height) * (top_pixel - (HEIGHT / 2) + (wall_height / 2));
	if (y_wall < 0)
		y_wall = 0;
	while (top_pixel < bottom_pixel)
	{
		mlx_put_pixel_screen(mlx, mlx->ray->rayon, top_pixel, reverse_bytes(color[(int)y_wall * texture->width + (int)x_wall]));
		y_wall +=(texture->height / wall_height);
		top_pixel++;
	}
}


void	render_wall(t_mlx *mlx, int ray)
{
	int	wall_height;
	double	bottom_pixel;
	double	top_pixel;	
	
	mlx->ray->distance *= cos(normalize_angle(mlx->ray->ray_angle - mlx->player->angle));
	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	mlx->ray->rayon = ray;
	draw_wall(mlx, top_pixel, bottom_pixel, wall_height);
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
}
