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

void free_texture(t_mlx *mlx)
{
	mlx_delete_texture(mlx->data->tex->no);
	mlx_delete_texture(mlx->data->tex->so);
	mlx_delete_texture(mlx->data->tex->we);
	mlx_delete_texture(mlx->data->tex->ea);
	mlx_delete_texture(mlx->data->tex->door);
	mlx_delete_texture(mlx->data->tex->barrel);
	mlx_delete_texture(mlx->data->tex->evil);
	if (mlx->data->tex->f)
		mlx_delete_texture(mlx->data->tex->f);
	if (mlx->data->tex->c)
		mlx_delete_texture(mlx->data->tex->c);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->mapi);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->lanterni);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->handkeyi);
	mlx_delete_image(mlx->mlx_p, mlx->data->tex->lanternemptyi);
	mlx_delete_texture(mlx->data->tex->map);
	mlx_delete_texture(mlx->data->tex->lantern);
	mlx_delete_texture(mlx->data->tex->lanternempty);
	mlx_delete_texture(mlx->data->tex->handkey);
	mlx_delete_image(mlx->mlx_p, mlx->msg);
	free(mlx->data->tex);
}

void	ft_exit(t_mlx *mlx)
{
	free(mlx->ray);
	free(mlx->player);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	free_texture(mlx);
	free_data(mlx->data, NULL);
	mlx_terminate(mlx->mlx_p);
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

int is_looking_at_door(double angle, double dir)
{
	double min;
	double max;

	min = dir - M_PI / 4;
	max = dir + M_PI / 4;
	angle -= M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle >= min && dir <= max)
		return (1);
	return (0);
}

void open_doors(t_mlx *mlx)
{
	double dir;

	if (mlx->data->map[mlx->player->player_y / TILE_SIZE - 1][mlx->player->player_x / TILE_SIZE] == 'D')
		dir = M_PI_ON_TWO;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE + 1][mlx->player->player_x / TILE_SIZE] == 'D')
		dir = M_THREE_PI_ON_TWO;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE - 1] == 'D')
		dir = M_PI;
	else if (mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE + 1] == 'D')
		dir = 0;
	else 
		return ;
	if (is_looking_at_door(mlx->player->angle, dir))
	{
		if (mlx->player->held_item == 2 && dir == 0)
			mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE + 1] = '0';
		else if (mlx->player->held_item == 2 && dir == M_PI)
			mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE - 1] = '0';
		else if (mlx->player->held_item == 2 && dir == M_THREE_PI_ON_TWO)
			mlx->data->map[mlx->player->player_y / TILE_SIZE + 1][mlx->player->player_x / TILE_SIZE] = '0';
		else if (mlx->player->held_item == 2 && dir == M_PI_ON_TWO)
			mlx->data->map[mlx->player->player_y / TILE_SIZE - 1][mlx->player->player_x / TILE_SIZE] = '0';
		else
			display_message(mlx, "I need the MAGIC SCROLL to destroy this barrier !");
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
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
	{
		if (mlx->player->can_run)
			mlx->player->is_sprinting = 1;
		else 
			mlx->player->is_sprinting = 0.5;
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		open_doors(mlx);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		if (mlx->player->held_item == 1)
		{
			mlx->player->held_item = 0;
			mlx->player->light_radius = DRAW_DISTANCE;
		}
		else
		{
			mlx->player->held_item = 1;
			if (mlx->player->fuel > 0)
				mlx->player->light_radius = DRAW_DISTANCE * 2;
			else 
				mlx->player->light_radius = DRAW_DISTANCE;
		}
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS )
	{
		if (mlx->player->held_item == 2)
			mlx->player->held_item = 0;
		else if (mlx->player->has_key)
		{
			mlx->player->held_item = 2;
			mlx->player->light_radius = DRAW_DISTANCE;
		}
	}
}

void press(mlx_key_data_t keydata, void *ml)
{
	t_mlx *mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_exit(mlx);
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
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_PRESS && mlx->player->can_run)
		mlx->player->is_sprinting = 2;
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
	if (mlx->data->map[map_grid_y][map_grid_x] != '1' && mlx->data->map[map_grid_y][map_grid_x] != 'D' && 
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
		move_x += -sin(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
		move_y += cos(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
	}
	if (mlx->player->is_moving_sides == 1)
	{
		move_x += sin(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
		move_y += -cos(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
	}
	if (mlx->player->is_moving_forward == -1)
	{
		move_x += cos(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
		move_y += sin(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
	}
	if (mlx->player->is_moving_forward == 1)
	{
		move_x += -cos(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
		move_y += -sin(mlx->player->angle) * PLAYER_SPEED * mlx->player->is_sprinting;
	}
	move_dude(mlx, move_x, move_y);
}

void	display_message(t_mlx *mlx, char *msg)
{
	if (mlx->msg)
		mlx_delete_image(mlx->mlx_p, mlx->msg);
	mlx->msg_counter = 250;
	mlx->msg = mlx_put_string(mlx->mlx_p, msg, TEXT_X, TEXT_Y); 
}

void	grab_key(t_mlx *mlx)
{
	if (mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE] == 'K')
	{
		display_message(mlx, "I found the MAGIC SCROLL ! I can use it to break the barriers.");
		mlx->player->has_key = 1;
		mlx->data->map[mlx->player->player_y / TILE_SIZE][mlx->player->player_x / TILE_SIZE] = '0';
	}
}

void	display_fuel(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < (int)((mlx->player->fuel / MAX_FUEL) * FUEL_MAX_LEN))
	{
		j = 0;
		while (j < FUEL_WIDTH)
		{
			mlx_put_pixel_screen(mlx, j + FUEL_POS_X, i + FUEL_POS_Y, FUEL_COLOR);
			j++;
		}
		i++;
	}
}

void	display_endurance(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < (int)((mlx->player->endurance / MAX_ENDURANCE) * ENDURANCE_MAX_LEN))
	{
		j = 0;
		while (j < ENDURANCE_WIDTH)
		{
			if (mlx->player->can_run)
				mlx_put_pixel_screen(mlx, j + ENDURANCE_POS_X, i + ENDURANCE_POS_Y, ENDURANCE_COLOR);
			else 
				mlx_put_pixel_screen(mlx, j + ENDURANCE_POS_X, i + ENDURANCE_POS_Y, ENDURANCE_SPENT);
			j++;
		}
		i++;
	}
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
	minimap_background(mlx);
	draw_minimap(mlx);
	if (mlx->player->held_item == 1 && mlx->player->fuel > 0)
		draw_lantern(mlx);
	else if (mlx->player->held_item == 1)
		draw_unlit_lantern(mlx);
	else if (mlx->player->held_item == 2)
		draw_key(mlx);
	grab_key(mlx);
	display_endurance(mlx);
	display_fuel(mlx);
	if (mlx->msg_counter > 0)
	{
		mlx->msg_counter--;
		redisplay_message(mlx);
	}
	else
	{
		mlx->msg_counter = -1;
		mlx_delete_image(mlx->mlx_p, mlx->msg);
		mlx->msg = NULL;
	}
	if (mlx->player->is_sprinting == 2)
		mlx->player->endurance--;
	else 
		mlx->player->endurance++;
	if (mlx->player->endurance <= 0)
	{
		mlx->player->can_run = 0;
		mlx->player->is_sprinting = 0.5;
	}
	if (mlx->player->endurance >= MIN_END_TO_RUN && mlx->player->can_run == 0)
	{
		mlx->player->can_run = 1;
		mlx->player->is_sprinting = 1;	
	}
	if (mlx->player->endurance >= MAX_ENDURANCE)
		mlx->player->endurance = MAX_ENDURANCE;
	if (mlx->player->held_item == 1)
		mlx->player->fuel--;
	if (mlx->player->fuel <= 0)
	{
		mlx->player->fuel = 0;
		mlx->player->light_radius = DRAW_DISTANCE;
	}
}

void	init_player(t_mlx mlx)
{
	mlx.player->player_x = mlx.data->player_x * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->player_y = mlx.data->player_y * TILE_SIZE + TILE_SIZE / 2;
	mlx.player->fov = (FOV * M_PI) / 180;
	if (mlx.data->player_orientation == 'N')
		mlx.player->angle = M_PI / 2;
	else if (mlx.data->player_orientation == 'S')
		mlx.player->angle = (3 / M_PI) / 2;
	else if (mlx.data->player_orientation == 'W')
		mlx.player->angle = M_PI;
	else 
		mlx.player->angle = 0;
}

void	load_img(t_mlx *mlx)
{
	mlx->data->tex->no = mlx_load_png(mlx->data->img->no);
	mlx->data->tex->so = mlx_load_png(mlx->data->img->so);
	mlx->data->tex->ea = mlx_load_png(mlx->data->img->ea);
	mlx->data->tex->we = mlx_load_png(mlx->data->img->we);
	mlx->data->tex->barrel = mlx_load_png("images/map.png");
	mlx->data->tex->evil = mlx_load_png("images/map.png");
	mlx->data->tex->door = mlx_load_png("images/DOOR.png");
	mlx->data->tex->map = mlx_load_png("images/map.png");
	mlx->data->tex->c = mlx_load_png("images/map.png");
	mlx->data->tex->f = mlx_load_png("images/map.png");
	mlx->data->tex->mapi = mlx_texture_to_image(mlx->mlx_p, mlx->data->tex->map);
	mlx->data->tex->lantern = mlx_load_png("images/Hand.png");
	mlx->data->tex->lanterni = mlx_texture_to_image(mlx->mlx_p, mlx->data->tex->lantern);
	mlx->data->tex->lanternempty = mlx_load_png("images/HandEmpty.png");
	mlx->data->tex->lanternemptyi = mlx_texture_to_image(mlx->mlx_p, mlx->data->tex->lanternempty);
	mlx->data->tex->handkey = mlx_load_png("images/key.png");
	mlx->data->tex->handkeyi = mlx_texture_to_image(mlx->mlx_p, mlx->data->tex->handkey);
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
	mlx->msg_counter = 250;
}

void start(t_data *data)
{
	t_mlx mlx;
	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	super_mega_init(&mlx);
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cube3D", 0);
	mlx.img = NULL;
	load_img(&mlx);
	init_player(mlx);
	mlx.msg = mlx_put_string(mlx.mlx_p, 
		"This place is cursed. I must find the MAGIC SCROLL to open the barriers and get away !", TEXT_X, TEXT_Y);
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
		start(data);
		free_data(data, NULL);
	}
	else 
	{
		printf("La carte !\n");
		return 0;
	}
}
