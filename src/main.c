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
	//cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void	init_player(t_mlx mlx)
{
	mlx.player->player_x = mlx.data->player_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->player_y = mlx.data->player_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	mlx.player->angle = M_PI;
}

void start(t_data *data)
{
	t_mlx mlx;
	mlx.data = data;
	mlx.mlx_p = calloc(1, sizeof(t_player));
	mlx.ray = calloc(1, sizeof(t_ray));
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cube3D", 0);
	init_player(mlx);
	mlx_loop_hook(mlx.mlx_p, &loop, &mlx);
	//mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
}

t_data	*init_map()
{
	t_data *data = calloc(1, sizeof(t_data));
	data->map = calloc(10, sizeof(char *));
	data->map[0] = strdup("1111111111111111111111111");
	data->map[1] = strdup("1000000000000000000100001");
	data->map[2] = strdup("1001000000000P00000000001");
	data->map[3] = strdup("1001000000000000001000001");
	data->map[4] = strdup("1001000000000000001000001");
	data->map[5] = strdup("1001000000100000001000001");
	data->map[6] = strdup("1001000000000000001000001");
	data->map[7] = strdup("1001000000001000001000001");
	data->map[8] = strdup("1111111111111111111111111");
	data->map[9] = NULL;
	data->player_y = 3;
	data->player_x = 14;
	data->map_width = 25;
	data->map_height = 9;     
	return (data);
}

int main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 2)
	{
		data = generate_data(argv[1]);
		if (!data)
			return (0);
		start(data);
		free_data(data, NULL);
	}
	return 0;
}
