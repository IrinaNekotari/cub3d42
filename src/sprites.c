/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:18:36 by mjuette           #+#    #+#             */
/*   Updated: 2024/04/19 18:18:38 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	mlx_put_pixel_screen2(t_mlx *mlx, int x, int y, int color)
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

double	get_x_sprite(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_wall;

	if (mlx->ray->flag == 1)
	{
		if ((mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI))
			x_wall = texture->width - (int)fmodf((mlx->ray->vert_x
						* (texture->width / TILE_SIZE)), texture->width);
		else
			x_wall = (int)fmodf((mlx->ray->vert_x
						* (texture->width / TILE_SIZE)), texture->width);
	}
	else
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3
			* (M_PI / 2))
			x_wall = texture->width - (int)fmodf((mlx->ray->horiz_x
						* (texture->width / TILE_SIZE)), texture->width);
		else
			x_wall = (int)fmodf((mlx->ray->horiz_x
						* (texture->width / TILE_SIZE)), texture->width);
	}
	return (x_wall);
}

mlx_texture_t	*get_texture_sprite(t_mlx *mlx)
{
	if (mlx->ray->wall_type == 'B')
		return (mlx->data->tex->barrel);
	else if (mlx->ray->wall_type == 'K')
		return (mlx->data->tex->key->current);
	else
		return (mlx->data->tex->evil);
}

void	draw_sprite(t_mlx *mlx, int top_pixel, int bottom_pixel,
	double sprite_height)
{
	double			x_wall;
	double			y_wall;
	uint32_t		*color;
	mlx_texture_t	*texture;

	texture = get_texture_sprite(mlx);
	color = (uint32_t *)texture->pixels;
	x_wall = get_x_sprite(texture, mlx);
	y_wall = (texture->height / sprite_height) * (top_pixel - (HEIGHT / 2)
			+ (sprite_height / 2));
	if (y_wall < 0)
		y_wall = 0;
	while (top_pixel < bottom_pixel)
	{
		mlx_put_pixel_screen2(mlx, mlx->ray->rayon, top_pixel,
			darken(reverse_bytes(color[(((int)y_wall) * texture->width)
					+ ((int)x_wall) % texture->width]),
				mlx->ray->distance, mlx));
		y_wall += (texture->height / sprite_height);
		top_pixel++;
	}
}

void	render_sprite(t_mlx *mlx, int ray, char method)
{
	int		wall_height;
	double	bottom_pixel;
	double	top_pixel;	

	if (mlx->ray->distance == 0)
		mlx->ray->distance = 0.001;
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
	mlx->ray->wall_type = method;
	draw_sprite(mlx, top_pixel, bottom_pixel, wall_height);
}
