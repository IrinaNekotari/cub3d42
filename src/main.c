/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:56:00 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/28 11:54:27 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_exit(t_mlx *mlx)
{
	int	i = 0;
	while (mlx->data->map[i])
		free(mlx->data->map[i++]);
	free(mlx->data->map);
	free(mlx->data);
	free(mlx->mlx_p);
	free(mlx->ray);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	printf("Closed\n");
	exit(0);
}

void loop(void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, WIDTH, HEIGHT);
	//hook(mlx, 0, 0);
	raycasting(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
	usleep(1000);
	mlx->player->angle += ROTATION_SPEED;
}

void	init_player(t_mlx mlx)
{
	mlx.player->player_x = mlx.data->player_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->player_y = mlx.data->player_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	mlx.player->angle = M_PI;
}

void	load_img(t_data *data)
{
	data->tex->no = mlx_load_png(data->img->no);
	data->tex->so = mlx_load_png(data->img->so);
	data->tex->ea = mlx_load_png(data->img->ea);
	data->tex->we = mlx_load_png(data->img->we);
}

void	super_mega_init(t_mlx *mlx)
{
	mlx->player->player_x = mlx->data->player_x;
        mlx->player->player_y = mlx->data->player_y;
        mlx->player->angle = 0;
        mlx->player->fov = 60;
        mlx->player->rotation = 0;
        mlx->player->left_right = 0;
        mlx->player->up_down = 0;
        mlx->ray->rayon = 0;
        mlx->ray->ray_angle = 0;
        mlx->ray->distance = 0;
        mlx->ray->flag = 0;
        mlx->ray->horiz_x = 0;
        mlx->ray->vert_y = 0;
}

void start(t_data *data)
{
	t_mlx mlx;
	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	super_mega_init(&mlx);
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cube3D", 0);
	init_player(mlx);
	mlx_loop_hook(mlx.mlx_p, &loop, &mlx);
	//mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
}

int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 2)
	{
		data = generate_data(argv[1]);
		if (!data)
			return (0);
		data->tex = ft_calloc(1, sizeof(t_texset));
		load_img(data);
		start(data);
		free_data(data, NULL);
	}
	return 0;
}
