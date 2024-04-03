/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:51:58 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/28 13:48:51 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	raycasting(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int	rayon;

	rayon = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
	while (rayon < WIDTH)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, normalize_angle(mlx->ray->ray_angle));
		v_inter = get_v_inter(mlx, normalize_angle(mlx->ray->ray_angle));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, rayon);
		rayon++;
		mlx->ray->ray_angle += (mlx->player->fov / WIDTH);
	}
}

float	get_v_inter(t_mlx *mlx, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int	pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->player->player_x, 2) + pow(v_y - mlx->player->player_y, 2)));
}

float   get_h_inter(t_mlx *mlx, float angle)
{
        float   h_x;
        float   h_y;
        float   x_step;
        float   y_step;
        int     pixel;

        y_step = TILE_SIZE;
        x_step = TILE_SIZE / tan(angle);
        h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
        pixel = inter_check(angle, &h_y, &y_step, 1);
        h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angle);
        if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
                x_step *= -1;
        while (wall_hit(h_x, h_y - pixel, mlx))
        {
                h_x += x_step;
                h_y += y_step;
        }
        mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
        return (sqrt(pow(h_x - mlx->player->player_x, 2) + pow(h_y - mlx->player->player_y, 2)));
}

int wall_hit(float x, float y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y< 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= mlx->data->map_height || x_m >= mlx->data->map_width))
		return (0);
	if (mlx->data->map[y_m] && x_m <= (int)strlen(mlx->data->map[y_m]))
		if (mlx->data->map[y_m][x_m] == '1')
				return (0);
	return (1);
}

int	inter_check(float angle, float *inter, float *step, int is_border_wall)
{
	if (is_border_wall)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}


