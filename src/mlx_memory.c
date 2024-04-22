/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:11:02 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 08:11:04 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_texture(t_mlx *mlx)
{
	mlx_delete_texture(mlx->data->tex->no);
	mlx_delete_texture(mlx->data->tex->so);
	mlx_delete_texture(mlx->data->tex->we);
	mlx_delete_texture(mlx->data->tex->ea);
	//mlx_delete_texture(mlx->data->tex->door);
	mlx_delete_texture(mlx->data->tex->barrel);
	//mlx_delete_texture(mlx->data->tex->key);
	mlx_delete_texture(mlx->data->tex->evil);
	if (mlx->data->tex->f)
		mlx_delete_texture(mlx->data->tex->f);
	if (mlx->data->tex->c)
		mlx_delete_texture(mlx->data->tex->c);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->mapi);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->lanterni);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->handkeyi);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->lanternemptyi);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->defeati);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->victoryi);
	mlx_delete_texture(mlx->data->tex->map);
	mlx_delete_texture(mlx->data->tex->lantern);
	mlx_delete_texture(mlx->data->tex->lanternempty);
	mlx_delete_texture(mlx->data->tex->handkey);
	mlx_delete_texture(mlx->data->tex->defeat);
	mlx_delete_texture(mlx->data->tex->victory);
	mlx_delete_image(mlx->mlx_p, mlx->msg);
	free(mlx->data->tex);
}

void	free_sprites(t_mlx *mlx)
{
	free_sprite(mlx->data->tex->door);
	free_sprite(mlx->data->tex->key);
	free(mlx->controller);
}

void	ft_exit(t_mlx *mlx)
{
	free(mlx->ray);
	free(mlx->player);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	free_texture(mlx);
	free_sprites(mlx);
	free_data(mlx->data, NULL);
	mlx_terminate(mlx->mlx_p);
	printf("Closed\n");
	exit(0);
}
