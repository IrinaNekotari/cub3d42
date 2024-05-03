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

void	ft_dist_order2(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->sprite->nb_sprite)
	{
		mlx->sprite->order[i] = i;
		mlx->sprite->dist[i] = ((mlx->player->player_x - mlx->sxy[i].x) *
				(mlx->player->player_x - mlx->sxy[i].x) + (mlx->player->player_y -
					mlx->sxy[i].y) * (mlx->player->player_y - mlx->sxy[i].y));
	}
}

void	ft_dist_order(t_mlx *mlx)
{
	int	i;
	int	j;
	double	tmp;
	
	ft_dist_order2(mlx);
	i = -1;
	while (++i < mlx->sprite->nb_sprite)
	{
		j = -1;
		while (++j < mlx->sprite->nb_sprite - 1)
		{
			if (mlx->sprite->dist[j] < mlx->sprite->dist[j+1])
			{
				tmp = mlx->sprite->dist[j];
				mlx->sprite->dist[j] = mlx->sprite->dist[j+1];
				mlx->sprite->dist[j+1] = tmp;
				tmp = mlx->sprite->order[j];
				mlx->sprite->order[j] = mlx->sprite->order[j+1];
				mlx->sprite->order[j+1] = (int)tmp;
			}
		}
	}
}

void	ft_calculs(t_mlx *mlx)
{
	mlx->sprite->invdet = 1.0 / (mlx->ray->planx * mlx->ray->diry -
			mlx->ray->dirx * mlx->ray->plany);
	mlx->sprite->transformx = mlx->sprite->invdet * (mlx->ray->diry *
			mlx->sprite->sprite_x - mlx->ray->dirx * mlx->sprite->sprite_y);
	mlx->sprite->transformy = mlx->sprite->invdet * (mlx->ray->plany *
			mlx->sprite->sprite_x - mlx->ray->planx * mlx->sprite->sprite_y);
	mlx->sprite->sprite_x = (int)((HEIGHT/ 2) * (1 + mlx->sprite->transformx
				/ mlx->sprite->transformy));
	mlx->sprite->sprite_height = abs((int)(mlx->ray->horiz_y / (mlx->sprite->transformy)));
	mlx->sprite->draw_start_y = -mlx->sprite->sprite_height / 2 + mlx->ray->horiz_y / 2;
	if (mlx->sprite->draw_start_y < 0)
		mlx->sprite->draw_start_y = 0;
	mlx->sprite->draw_end_y = mlx->sprite->sprite_height / 2 + mlx->ray->horiz_y / 2;
	if (mlx->sprite->draw_end_y >= mlx->ray->horiz_y)
		mlx->sprite->draw_end_y = mlx->ray->horiz_y;
	mlx->sprite->sprite_width = (int)(WIDTH / (mlx->sprite->transformy)) + 1;
	mlx->sprite->draw_start_x = -mlx->sprite->sprite_width / 2 + mlx->sprite->sprite_x;
	if (mlx->sprite->draw_start_x < 0)
		mlx->sprite->draw_start_x = 0;
	mlx->sprite->draw_end_x = mlx->sprite->sprite_width / 2 + mlx->sprite->sprite_x;
	if (mlx->sprite->draw_end_x >= mlx->ray->horiz_x)
		mlx->sprite->draw_end_x = mlx->ray->horiz_x;
}

void	draw_sprite(t_mlx *mlx, int top_pixel, int bottom_pixel,
	double sprite_height)
{
	/*
	int		texy;
	uint32_t		*color;
	mlx_texture_t	*texture;
	
	texture = mlx->data->tex->barrel;
	color = (uint32_t *)texture->pixels;
	
	while (y < mlx->sprite->draw_end_y)
	{
		d = (y) * 256 - HEIGHT * 128 + mlx->sprite->sprite_height * 128;
		texy = ((d * mlx->data->tex->barrel->height) / mlx->sprite->sprite_height) / 256;
		mlx_put_pixel_screen(mlx, texx, stripe,
			darken(reverse_bytes(color[((int)texy * texture->width)
					+ ((int)texx) % texture->width]),
				*mlx->sprite->dist, mlx));
		y++;
	}*/
	double			x_wall;
	double			y_wall;
	uint32_t		*color;
	mlx_texture_t	*texture;

	texture = mlx->data->tex->barrel;
	color = (uint32_t *)texture->pixels;
	x_wall = get_x_wall(texture, mlx);
	y_wall = (texture->height / sprite_height) * (top_pixel - (HEIGHT / 2)
			+ (sprite_height / 2));
	if (y_wall < 0)
		y_wall = 0;
	while (top_pixel < bottom_pixel)
	{
		mlx_put_pixel_screen(mlx, mlx->ray->rayon, top_pixel,
			darken(reverse_bytes(color[((int)y_wall * texture->width)
					+ ((int)x_wall) % texture->width]),
				mlx->ray->distance, mlx));
		y_wall += (texture->height / sprite_height);
		top_pixel++;
	}
}

void	render_sprite(t_mlx *mlx, int ray)
{
	/*int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	//ft_dist_order(mlx);
	while (++i < mlx->sprite->nb_sprite)
	{
		ft_calculs(mlx, i);
		stripe = mlx->sprite->draw_start_x;
		while (stripe < mlx->sprite->draw_end_x)
		{
			texx = (int)(256 * (stripe - (-mlx->sprite->sprite_width / 2 +
					mlx->sprite->sprite_x)) * mlx->data->tex->barrel->width
					/ mlx->sprite->sprite_width) / 256;
			if (mlx->sprite->transformy > 0 && stripe >= 0 && stripe < mlx->ray->horiz_x
					&& mlx->sprite->transformy < mlx->sprite->zBuffer[stripe])
			{
				y = mlx->sprite->draw_start_y;
				draw_sprite(mlx, y, texx, stripe);
			}
			stripe++;
		}
	}*/
	int		wall_height;
	double	bottom_pixel;
	double	top_pixel;	

	mlx->ray->distance *= cos(normalize_angle
			(mlx->ray->ray_angle - mlx->player->angle));
	if (mlx->ray->distance == 0)
		mlx->ray->distance = 0.001;
	wall_height = (TILE_SIZE / mlx->ray->distance)
		* ((WIDTH / 2) / tan(mlx->player->fov / 2));
	mlx->h[ray] = wall_height;
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
	draw_sprite(mlx, top_pixel, bottom_pixel, wall_height);
}

