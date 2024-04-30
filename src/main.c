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

void	start(t_data *data)
{
	t_mlx	mlx;

	mlx.data = data;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, sizeof(t_ray));
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, "Cube3D", 0);
	mlx.img = NULL;
	super_mega_init(&mlx);
	load_img(&mlx);
	mlx.msg = mlx_put_string(mlx.mlx_p, LINE_INTRO, 0, 0);
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
