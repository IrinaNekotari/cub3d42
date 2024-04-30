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
				tmp = mlx->sprite->[j];
				mlx->sprite->dist[j] = mlx->sprite->dist[j+1];
				mlx->sprite->dist[j+1] = tmp;
				tmp = mlx->sprite[j];
				mlx->sprite->order[j] = mlx->sprite->order[j+1];
				mlx->sprite->order[j+1] = (int)tmp;
			}
		}
	}
}

void	ft_calculs(t_mlx *mlx, int i)
{
	mlx->sprite->sprite_x = mlx->sxy[mlx->sprite->order[i].x - (mlx->player->player_x * TILE_SIZE);
	mlx->sprite->sprite_y = mlx->sxy[mlx->sprite->order[i].y - (mlx->player->player_y * TILE_SIZE);
	mlx->sprite->invdet = 1.0 / (mlx->ray.planx * mlx->ray.diry -
			recup->ray.dirx * mlx->ray.plany);
	mlx->sprite->transformx = mlx->sprite.invdet * (mlx->ray.diry *
			mlx->sprite.spritex - mlx->ray.dirx * mlx->sprite.spritey);
	mlx->sprite->transformy = mlx->sprite.invdet * (mlx->ray.plany *
			mlx->sprite.spritex - mlx->ray.planx * mlx->sprite.spritey);
	mlx->sprite.sprite_x = (int)((mlx->ray->horiz_x / 2) * (1 + mlx->sprite.transformx
				/ mlx->sprite.transformy));
	mlx->sprite.sprite_height = abs((int)(mlx->ray->horiz_y / (mlx->sprite.transformy)));
	mlx->sprite.draw_start_y = -mlx->sprite.sprite_height / 2 + mlx->horiz_y / 2;
	if (mlx->sprite.draw_start_y < 0)
		mlx->sprite.draw_start_y = 0;
	mlx->sprite.draw_end_y = mlx->sprite.sprite_height / 2 + mlx->horiz_y / 2;
	if (mlx->sprite.draw_end_y >= mlx->ray->horiz_y)
		mlx->sprite.drawendy = mlx->ray->horiz_y;
	mlx->sprite.sprite_width = abs((int)(mlx->horiz_y / (mlx->sprite.transformy)));
	mlx->sprite.draw_start_x = -mlx->sprite.sprite_width / 2 + recup->sprite.sprite_x;
	if (mlx->sprite.draw_start_x < 0)
		mlx->sprite.draw_start_x = 0;
	mlx->sprite.draw_end_x = mlx->sprite.sprite_width / 2 + mlx->sprite.sprite_x;
	if (mlx->sprite.draw_end_x >= mlx->ray->horiz_x)
		mlx->sprite.draw_end_x = mlx->ray->horiz_x;
}

void	draw_sprite(t_mlx *mlx, int y, int texx, int stripe)
{
	
	int		d;
	int		texy;
	uint32_t		*color;
	
	color = (uint32_t *)texture->pixels;
	while (y < mlx->sprite.draw_end_y)
	{
		d = (y) * 256 - HEIGHT * 128 + mlx->sprite.sprite_height * 128;
		texy = ((d * mlx->data->tex->barrel->height) / mlx->sprite.sprite_height) / 256;
		mlx_put_pixel_screen(mlx, texx, stripe,
			darken(reverse_bytes(color[((int)texy * texture->width)
					+ ((int)texx) % texture->width]),
				mlx->sprite->dist, mlx));
		y++;
	}
}

void	render_sprite(t_mlx *mlx)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_dist_order(mlx);
	while (++i < mlx->sprite.nb_sprite)
	{
		ft_calculs(mlx, i);
		stripe = mlx->sprite.draw_start_x;
		while (stripe < mlx->sprite.draw_end_x)
		{
			texx = (int)(256 * (stripe - (-mlx->sprite.sprite_width / 2 +
					mlx->sprite.sprite_x)) * mlx->data->tex->barrel->width
					/ mlx->sprite.sprite_width) / 256;
			if (mlx->sprite.transformy > 0 && stripe >= 0 && stripe < mlx->ray->horiz_x
					&& mlx->sprite.transformy < mlx->sprite.zBuffer[stripe])
			{
				y = mlx->sprite.draw_start_y;
				draw_sprite(mlx, y, texx, stripe);
			}
			stripe++;
		}
	}
}

