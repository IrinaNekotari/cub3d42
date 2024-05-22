/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:42:41 by mjuette           #+#    #+#             */
/*   Updated: 2024/05/14 14:48:50 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	deal_mouse(double posx, double posy, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_get_mouse_pos(mlx->mlx_p, (int32_t *)&posx, (int32_t *)&posy);
	if (posx > mlx->data->mouse_x)
		mlx->player->angle += SENSI_MOUSE;
	else if (posx < mlx->data->mouse_x)
		mlx->player->angle -= SENSI_MOUSE;
	mlx_set_mouse_pos(mlx->mlx_p, WIDTH / 2, HEIGHT / 2);
}
