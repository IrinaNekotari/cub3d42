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
	if (color == 0x00000000)
		return ;
	mlx_put_pixel(mlx->img, x , y, color);
}

void	draw_square2(t_mlx *mlx, int x, int y, int c)
{
	int i;
	int j;

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
	int i;
	int j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE )
		{
			mlx_put_pixel_screen(mlx, j + x + 6 * MINIMAP_SIZE + MINIMAP_SIZE / 2, i + y + 4 *MINIMAP_SIZE + MINIMAP_SIZE / 2, c);
			j++;
		}
		i++;
	}
}

int32_t mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y) 
{
	uint8_t *pixelstart;

	if (x > image->width || y > image->height)
		return (0x00000000);
	pixelstart = image->pixels + (y * image->width + x) * sizeof(int32_t);
	if (*(pixelstart + 3) == 0)
		return (0x00000000);
	return get_rgba(*(pixelstart), *(pixelstart + 1),
		* (pixelstart + 2), *(pixelstart + 3));
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	i;
	int	c;

	i = bottom_pixel;
	c = mlx->data->img->floor_color;
	while (i < HEIGHT)
	{
		mlx_put_pixel_screen(mlx, ray, i, darken(c, HEIGHT - i - 45, mlx));
		i++;
	}
	c = mlx->data->img->ceiling_color;
	i = 0;
	while (i < top_pixel)
		{
		mlx_put_pixel_screen(mlx, ray, i, darken(c, i - 45, mlx));
		i++;
	}
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = normalize_angle(mlx->ray->ray_angle);
	if (mlx->ray->wall_type == 'D')
			return (mlx->data->tex->door);
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

int	darken(int c, double dist, t_mlx *mlx)
{
	int r;
	int g;
	int b;

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
		mlx_put_pixel_screen(mlx, mlx->ray->rayon, top_pixel, darken(reverse_bytes(color[(int)y_wall * texture->width + (int)x_wall]), mlx->ray->distance, mlx));
		y_wall +=(texture->height / wall_height);
		top_pixel++;
	}
}

//La ligne qui faisait planter etait la
//La distance pouvait etre 0
//Et comme on divisait par cette derniere ...
void	render_wall(t_mlx *mlx, int ray)
{
	int	wall_height;
	double	bottom_pixel;
	double	top_pixel;	
	
	mlx->ray->distance *= cos(normalize_angle(mlx->ray->ray_angle - mlx->player->angle));
	if (mlx->ray->distance == 0)
		mlx->ray->distance = 0.001;
	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (top_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	mlx->ray->rayon = ray;
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
	draw_wall(mlx, top_pixel, bottom_pixel, wall_height);
	//choose_display(mlx, top_pixel, bottom_pixel, wall_height);
	//draw_darkness(mlx, ray);
}