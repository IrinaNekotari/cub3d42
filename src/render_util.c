/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:55:12 by mjuette           #+#    #+#             */
/*   Updated: 2024/05/14 13:55:18 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	mlx_put_floor(t_mlx *mlx, int i, int ray, int c)
{
	while (i < HEIGHT)
	{
		if (!mlx->data->img->floor_img)
			mlx_put_pixel_screen(mlx, ray, i, darken(c, HEIGHT - i - 45, mlx));
		i++;
	}
}
