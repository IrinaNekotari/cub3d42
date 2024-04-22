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

void	init_player(t_mlx mlx)
{
	mlx.player->player_x = mlx.data->player_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->player_y = mlx.data->player_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	if (mlx.data->player_orientation == 'S')
		mlx.player->angle = M_PI / 2;
	else if (mlx.data->player_orientation == 'N')
		mlx.player->angle = (3 * M_PI) / 2;
	else if (mlx.data->player_orientation == 'W')
		mlx.player->angle = M_PI;
	else
		mlx.player->angle = 0;
}

void	free_sprite(t_sprite *s)
{
	int	i;

	i = 0;
	while (i < IMAGES_IN_SPRITES)
	{
		if (s->sprites[i])
			mlx_delete_texture(s->sprites[i]);
		i++;
	}
	free(s);
}

void	load_sprites(t_mlx **mlx)
{
	(*mlx)->data->tex->door = create_sprite(4);
	(*mlx)->data->tex->key = create_sprite(4);
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

void	load_img(t_mlx *mlx)
{
	mlx->data->tex->no = mlx_load_png(mlx->data->img->no);
	mlx->data->tex->so = mlx_load_png(mlx->data->img->so);
	mlx->data->tex->ea = mlx_load_png(mlx->data->img->ea);
	mlx->data->tex->we = mlx_load_png(mlx->data->img->we);
	mlx->data->tex->barrel = mlx_load_png("images/Barrel.png");
	mlx->data->tex->evil = mlx_load_png("images/map.png");
	mlx->data->tex->map = mlx_load_png("images/map.png");
	mlx->data->tex->c = mlx_load_png("images/map.png");
	mlx->data->tex->f = mlx_load_png("images/map.png");
	mlx->data->tex->mapi = mlx_texture_to_image
		(mlx->mlx_p, mlx->data->tex->map);
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
	load_sprites(&mlx);
}

void	super_mega_init(t_mlx *mlx)
{
	mlx->player->player_x = mlx->data->player_x;
	mlx->player->player_y = mlx->data->player_y;
	mlx->player->light_radius = DRAW_DISTANCE;
	mlx->player->held_item = 0;
	mlx->player->is_sprinting = 1;
	mlx->player->has_key = 0;
	mlx->player->endurance = MAX_ENDURANCE;
	mlx->player->can_run = 1;
	mlx->player->fuel = MAX_FUEL;
	mlx->player->fov = FOV;
	mlx->player->is_rotating = 0;
	mlx->player->is_moving_sides = 0;
	mlx->player->is_moving_forward = 0;
	mlx->player->rotation = 0;
	mlx->player->left_right = 0;
	mlx->player->up_down = 0;
	mlx->ray->rayon = 0;
	mlx->ray->ray_angle = 0;
	mlx->ray->distance = 0;
	mlx->ray->flag = 0;
	mlx->ray->wall_type = 0;
	mlx->ray->horiz_x = 0;
	mlx->ray->vert_y = 0;
	mlx->msg_counter = 250;
	mlx->data->victory = 0;
	mlx->data->evil_x = -1;
	mlx->data->evil_y = -1;
	mlx->controller = init_controller();
}
