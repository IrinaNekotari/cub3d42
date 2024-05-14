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

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int				i;
	int				c;
	uint32_t		*color;
	mlx_texture_t	*texture;

	i = bottom_pixel;
	c = mlx->data->img->floor_color;
	while (i < HEIGHT)
	{
		if (!mlx->data->img->floor_img)
			mlx_put_pixel_screen(mlx, ray, i, darken(c, HEIGHT - i - 45, mlx));
		i++;
	}
	texture = mlx->data->tex->c;
	if (texture)
		color = (uint32_t *)texture->pixels;
	c = mlx->data->img->ceiling_color;
	i = 0;
	while (i < top_pixel)
	{
		if (!mlx->data->img->ceiling_img)
			mlx_put_pixel_screen(mlx, ray, i, darken(c, i - 45, mlx));
		else
			mlx_put_pixel_screen(mlx, ray, i,
				darken(reverse_bytes(color[(i % texture->width * texture->width)
						+ (ray) % texture->width]),
					i - 45, mlx));
		i++;
	}
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = normalize_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->wall_type == 'D')
			return (mlx->data->tex->door->current);
		if (mlx->ray->wall_type == 'X')
			return (mlx->data->tex->exit);
		if (mlx->ray->ray_angle > M_PI / 2
			&& mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->data->tex->ea);
		else
			return (mlx->data->tex->we);
	}
	else
	{
		if (mlx->ray->wall_type2 == 'D')
			return (mlx->data->tex->door->current);
		if (mlx->ray->wall_type2 == 'X')
			return (mlx->data->tex->exit);
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->data->tex->so);
		else
			return (mlx->data->tex->no);
	}
}

double	get_x_wall(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_wall;

	if (mlx->ray->flag == 1)
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			x_wall = texture->width - (int)fmod((mlx->ray->horiz_x
						* (texture->width / TILE_SIZE)), texture->width);
		else
			x_wall = (int)fmodf((mlx->ray->horiz_x
						* (texture->width / TILE_SIZE)), texture->width);
	}
	else
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3
			* (M_PI / 2) && mlx->ray->wall_type != 'D')
			x_wall = texture->width - (int)fmod((mlx->ray->vert_y
						* (texture->width / TILE_SIZE)), texture->width);
		else
			x_wall = (int)fmodf((mlx->ray->vert_y
						* (texture->width / TILE_SIZE)), texture->width);
	}
	return (x_wall);
}

void	draw_wall(t_mlx *mlx, int top_pixel, int bottom_pixel,
	double wall_height)
{
	double			x_wall;
	double			y_wall;
	uint32_t		*color;
	mlx_texture_t	*texture;

	texture = get_texture(mlx, mlx->ray->flag);
	color = (uint32_t *)texture->pixels;
	x_wall = get_x_wall(texture, mlx);
	y_wall = (texture->height / wall_height) * (top_pixel - (HEIGHT / 2)
			+ (wall_height / 2));
	if (y_wall < 0)
		y_wall = 0;
	while (top_pixel < bottom_pixel)
	{
		mlx_put_pixel_screen(mlx, mlx->ray->rayon, top_pixel,
			darken(reverse_bytes(color[((int)y_wall * texture->width)
					+ ((int)x_wall) % texture->width]),
				mlx->ray->distance, mlx));
		y_wall += (texture->height / wall_height);
		top_pixel++;
	}
}

void	render_wall(t_mlx *mlx, int ray)
{
	int		wall_height;
	double	bottom_pixel;
	double	top_pixel;	

	mlx->ray->distance *= cos(normalize_angle
			(mlx->ray->ray_angle - mlx->player->angle));
	if (mlx->ray->distance <= 0)
		mlx->ray->distance = 0.01;
	wall_height = (TILE_SIZE / mlx->ray->distance)
		* ((WIDTH / 2) / tan(mlx->player->fov / 2));
	if (wall_height == 0)
		wall_height = 1;
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (top_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	mlx->ray->rayon = ray;
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
	draw_wall(mlx, top_pixel, bottom_pixel, wall_height);
}
