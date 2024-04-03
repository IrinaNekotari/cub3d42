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

void rotato(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED / 10;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED / 10;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void release(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->player->is_rotating = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->player->is_rotating = 0;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_forward = 0;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_forward = 0;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_sides = 0;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		mlx->player->is_moving_sides = 0;
}

void press(mlx_key_data_t keydata, void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->player->is_rotating = -1;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->player->is_rotating = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->player->is_moving_forward = -1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		mlx->player->is_moving_forward = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		mlx->player->is_moving_sides = 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		mlx->player->is_moving_sides = -1;
	release(keydata, mlx);
}
void move_dude(t_mlx *mlx, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->data->map[map_grid_y][map_grid_x] != '1' && 
	(mlx->data->map[map_grid_y][mlx->player->player_x / TILE_SIZE] != '1' &&
	mlx->data->map[mlx->player->player_y / TILE_SIZE][map_grid_x] != '1'))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

void move(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->is_rotating == 1)
		rotato(mlx, 1);
	if (mlx->player->is_rotating == -1)
		rotato(mlx, 0);
	if (mlx->player->is_moving_sides == -1)
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->is_moving_sides == 1)
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->is_moving_forward == -1)
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->is_moving_forward == 1)
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	move_dude(mlx, move_x, move_y);
}

void loop(void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, WIDTH, HEIGHT);
	move(mlx, 0, 0);
	raycasting(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
	ft_printf("Position of player %dx%d(angle %d deg)\n", mlx->player->player_x, mlx->player->player_y, mlx->player->angle);
	ft_printf("Position on map %dx%d\n", mlx->player->player_x / TILE_SIZE, mlx->player->player_y / TILE_SIZE);
	//TILE_SIZE
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
	mlx_key_hook(mlx.mlx_p, &press, &mlx);
	mlx_loop_hook(mlx.mlx_p, &loop, &mlx);
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
