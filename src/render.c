/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuette <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:33 by mjuette           #+#    #+#             */
/*   Updated: 2024/03/28 09:51:47 by mjuette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	i;
	int	c;

	i = b_pix;
	c = get_rgba(ft_atoi(mlx->data->couleur_plafond[0]), ft_atoi(mlx->data->couleur_plafond[1]), ft_atoi(mlx->data->couleur_plafond[2]), 255);
	while (i < HEIGHT)
		mlx_put_pixel_goat(mlx, ray, i++, c);
	c = get_rgba(ft_atoi(mlx->data->couleur_sol[0]), ft_atoi(mlx_data->couleur_sol[1]), ft_atoi(mlx->data->couleur_sol[2]), 255);
	i = 0;
	while (i < t_pix)
		mlx_put_pixel_goat(mlx, ray, i++, c);
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_ngl = normalize_angle(mlx->ray->ray_ngl);
	if (flag = 0)
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (mlx->tex->ea);
		else
			return (mlx->tex->we);
	}
	else
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (mlx->tex->so);
		else
			return (mlx->tex->no);
	}
}

