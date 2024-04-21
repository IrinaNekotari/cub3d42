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

void	tick1(t_mlx *mlx)
{
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
	if (mlx->player->is_sprinting == 2
		&& (mlx->player->is_moving_forward != 0
			|| mlx->player->is_moving_sides != 0))
		mlx->player->endurance--;
	else
		mlx->player->endurance++;
}

void	tick2(t_mlx *mlx)
{
	if (mlx->player->endurance <= 0)
	{
		mlx->player->can_run = 0;
		mlx->player->is_sprinting = 0.5;
	}
	if (mlx->player->endurance >= MIN_END_TO_RUN
		&& mlx->player->can_run == 0)
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

void	victory_screen(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)mlx->data->tex->victoryi->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->victoryi->width)
		{
			mlx_put_pixel_screen(mlx, j + (WIDTH / 2 - mlx->data->tex->victoryi->width / 2),
				i + (HEIGHT / 2 - (int)mlx->data->tex->victoryi->height / 2), mlx_get_pixel(mlx->data->tex->victoryi, j, i));
			j++;
		}
		i++;
	}
}

void	defeat_screen(t_mlx *mlx)
{
	int	i;
	int	j;
 
	i = 0;
	while (i < (int)mlx->data->tex->defeati->height)
	{
		j = 0;
		while (j < (int)mlx->data->tex->defeati->width)
		{
			mlx_put_pixel_screen(mlx, j + (WIDTH / 2 - mlx->data->tex->defeati->width / 2),
					i + (HEIGHT / 2 - (int)mlx->data->tex->defeati->height / 2), mlx_get_pixel(mlx->data->tex->defeati, j, i));
			j++;
		}
		i++;
	}
}

void	loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (!mlx->data->victory)
	{
		mlx_delete_image(mlx->mlx_p, mlx->img);
		mlx->img = mlx_new_image(mlx->mlx_p, WIDTH, HEIGHT);
		mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
		raycasting(mlx);
		//raycasting_door(mlx);
		redisplay_message(mlx);
		move(mlx, 0, 0);
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
		tick1(mlx);
		tick2(mlx);
	}
	else if (mlx->data->victory == 1)
	{
		mlx->data->x++;
		if (mlx->data->x >= TIME_TO_END * 2)
			ft_exit(mlx);
		victory(mlx);
		victory_screen(mlx);
	}
	else 
	{
		mlx->data->x++;
		if (mlx->data->x >= (TIME_TO_END * 2))
			ft_exit(mlx);
		defeat(mlx);
		defeat_screen(mlx);
	}
}

void	start(t_data *data)
{
	t_mlx	mlx;

	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	super_mega_init(&mlx);
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cube3D", 0);
	mlx.img = NULL;
	load_img(&mlx);
	init_player(mlx);
	mlx.msg = mlx_put_string(mlx.mlx_p, LINE_INTRO, TEXT_X, TEXT_Y);
	//display_message(&mlx, LINE_INTRO);
	mlx_key_hook(mlx.mlx_p, &press, &mlx);
	mlx_loop_hook(mlx.mlx_p, &loop, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
}

int	main(int argc, char *argv[])
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
		return (0);
	}
}
