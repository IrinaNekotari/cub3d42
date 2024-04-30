/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:57:51 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 07:57:53 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Regarde dans la map, et récupère la position 
 * initiale de la vilaine creature.
*/
void	get_position_evil(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'V')
			{
				data->evil_x = j;
				data->evil_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	data->evil_x = -1;
	data->evil_y = -1;
}

/**
 * Regarde dans la map, et récupère la position 
 * et l'orientation initiale du joueur.
*/
void	get_positions(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player_x = j;
				data->player_y = i;
				data->player_orientation = data->map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}
