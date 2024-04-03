/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:03:06 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/03 10:03:07 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/**
 * Ces 4 fonctions sont des sous-divions de generate_imgset
*/

int	part_one_img(t_imgset **img, char **li)
{
	if (ft_equals(li[0], "NO"))
	{
		if ((*img)->no)
			free((*img)->no);
		(*img)->no = ft_strdup(li[1]);
		return (1);
	}
	if (ft_equals(li[0], "SO"))
	{
		if ((*img)->so)
			free((*img)->so);
		(*img)->so = ft_strdup(li[1]);
		return (1);
	}
	return (0);
}

int	part_two_img(t_imgset **img, char **li)
{
	if (ft_equals(li[0], "EA"))
	{
		if ((*img)->ea)
			free((*img)->ea);
		(*img)->ea = ft_strdup(li[1]);
		return (1);
	}
	if (ft_equals(li[0], "WE"))
	{
		if ((*img)->we)
			free((*img)->we);
		(*img)->we = ft_strdup(li[1]);
		return (1);
	}
	return (0);
}

int	part_three_img(t_imgset **img, char **li)
{
	if (ft_equals(li[0], "C") && is_rgb(li[1]))
	{
		(*img)->ceiling_color = get_rgb(li[1]);
		if ((*img)->ceiling_color == -1)
			return (0);
		return (1);
	}
	else if (ft_equals(li[0], "C") && !is_rgb(li[1]))
	{
		if ((*img)->ceiling_img)
			free((*img)->ceiling_img);
		(*img)->ceiling_img = ft_strdup(li[1]);
		if (ft_strchr((*img)->ceiling_img, ','))
			return (0);
		return (1);
	}
	return (-1);
}

int	part_four_img(t_imgset **img, char **li)
{
	if (ft_equals(li[0], "F") && is_rgb(li[1]))
	{
		(*img)->floor_color = get_rgb(li[1]);
		if ((*img)->floor_color == -1)
			return (0);
		return (1);
	}
	else if (ft_equals(li[0], "F") && !is_rgb(li[1]))
	{
		if ((*img)->floor_img)
			free((*img)->floor_img);
		(*img)->floor_img = ft_strdup(li[1]);
		if (ft_strchr((*img)->floor_img, ','))
			return (0);
		return (1);
	}
	return (-1);
}
