/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:19:08 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/16 09:19:09 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	load_sprites(t_mlx **mlx)
{
	(*mlx)->data->tex->door = create_sprite(10);
	(*mlx)->data->tex->key = create_sprite(10);
	add_to_set((*mlx)->data->tex->door, "images/doorA.png");
	add_to_set((*mlx)->data->tex->door, "images/doorB.png");
	add_to_set((*mlx)->data->tex->door, "images/doorC.png");
	add_to_set((*mlx)->data->tex->door, "images/doorD.png");
	add_to_set((*mlx)->data->tex->door, "images/doorE.png");
	add_to_set((*mlx)->data->tex->door, "images/doorF.png");
	add_to_set((*mlx)->data->tex->key, "images/Scroll.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollB.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollC.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollD.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollE.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollD.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollC.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollB.png");
	add_to_set((*mlx)->data->tex->key, "images/Scroll.png");
	add_to_set((*mlx)->data->tex->key, "images/ScrollF.png");
	add_to_control((*mlx)->controller, (*mlx)->data->tex->door);
	add_to_control((*mlx)->controller, (*mlx)->data->tex->key);
}

void	load_img2(t_mlx *mlx)
{
	mlx->data->tex->lantern = mlx_load_png("images/Hand.png");
	mlx->data->tex->lanterni = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->lantern);
	mlx->data->tex->lanternempty = mlx_load_png
		("images/HandEmpty.png");
	mlx->data->tex->lanternemptyi = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->lanternempty);
	mlx->data->tex->handkey = mlx_load_png("images/key.png");
	mlx->data->tex->handkeyi = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->handkey);
	mlx->data->tex->victory = mlx_load_png("images/victory.png");
	mlx->data->tex->victoryi = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->victory);
	mlx->data->tex->defeat = mlx_load_png("images/died.png");
	mlx->data->tex->defeati = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->defeat);
}

void	load_img(t_mlx *mlx)
{
	mlx->data->tex->no = mlx_load_png(mlx->data->img->no);
	mlx->data->tex->so = mlx_load_png(mlx->data->img->so);
	mlx->data->tex->ea = mlx_load_png(mlx->data->img->ea);
	mlx->data->tex->we = mlx_load_png(mlx->data->img->we);
	mlx->data->tex->barrel = mlx_load_png("images/Barrel.png");
	mlx->data->tex->evil = mlx_load_png("images/map.png");
	mlx->data->tex->map = mlx_load_png("images/map.png");
	if (mlx->data->img->floor_img)
		mlx->data->tex->f = mlx_load_png(mlx->data->img->floor_img);
	if (mlx->data->img->ceiling_img)
		mlx->data->tex->c = mlx_load_png(mlx->data->img->ceiling_img);
	mlx->data->tex->exit = mlx_load_png("images/exit.png");
	mlx->data->tex->mapi = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->map);
	load_img2(mlx);
	load_sprites(&mlx);
}
